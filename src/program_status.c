/* vi:set ts=8 sts=4 sw=4 noet:
 *
 * VIM - Vi IMproved	by Bram Moolenaar
 *
 * Do ":help uganda"  in Vim to read copying and usage conditions.
 * Do ":help credits" in Vim to see a list of people who contributed.
 * See README.txt for an overview of the Vim source code.
 */

/*
 * program_status.c: OSC 7501 program status reports, so rootshell can show
 * what Vim is doing.
 * Spec: https://www.superlogical.com/rex/docs/build/program-status
 */

#include "vim.h"

#if defined(VIM_APPLE_SANDBOX) || defined(PROTO)

#define PS_MAX_TITLE	192
#define PS_MAX_MSG	2048

// Thread-local like the rest of Vim's state, so concurrent sessions don't mix.
static __thread char_u	*last_body = NULL;
static __thread char_u	*quit_refused = NULL;
static __thread char_u	*write_error = NULL;
static __thread int	write_failed_now = FALSE;	// since the last typed key

static const char ps_base64[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    static char_u *
ps_buf_name(buf_T *buf)
{
    char_u *name = buf_spname(buf);

    return name != NULL ? name : buf->b_fname;
}

/*
 * Append ":key=" and "text" in base64.  Control characters become spaces and
 * invalid UTF-8 becomes '?' (the terminal discards either), then the text is
 * cut on a character boundary to "max" bytes.
 */
    static void
ps_append_text(garray_T *gap, char *key, char_u *text, int max)
{
    char_u	clean[PS_MAX_MSG + 1];
    int		len = 0;
    char_u	*p;
    int		i;

    for (p = skipwhite(text); *p != NUL; )
    {
	int l = utf_ptr2len(p);
	int c = utf_ptr2char(p);

	if (l == 1 && *p >= 0x80)
	    c = '?';
	if (c < 0x20 || c == 0x7f || (c >= 0x80 && c <= 0x9f))
	    c = ' ';
	if (c == ' ' || c == '?')
	    l = 1;
	if (len + l > max)
	    break;
	if (l == 1)
	    clean[len] = c;
	else
	    mch_memmove(clean + len, p, l);
	len += l;
	p += utf_ptr2len(p);
    }
    while (len > 0 && clean[len - 1] == ' ')
	--len;
    if (len == 0)
	return;

    ga_concat(gap, (char_u *)":");
    ga_concat(gap, (char_u *)key);
    ga_concat(gap, (char_u *)"=");
    for (i = 0; i < len; i += 3)
    {
	int_u	n = (int_u)clean[i] << 16;
	int	left = len - i;

	if (left > 1)
	    n |= (int_u)clean[i + 1] << 8;
	if (left > 2)
	    n |= clean[i + 2];
	ga_append(gap, ps_base64[(n >> 18) & 63]);
	ga_append(gap, ps_base64[(n >> 12) & 63]);
	ga_append(gap, left > 1 ? ps_base64[(n >> 6) & 63] : '=');
	ga_append(gap, left > 2 ? ps_base64[n & 63] : '=');
    }
}

    static int
ps_any_modified(void)
{
    buf_T *buf;

    FOR_ALL_BUFFERS(buf)
	if (bufIsChanged(buf))
	    return TRUE;
    return FALSE;
}

    static void
ps_emit(char_u *body)
{
    out_str_nf((char_u *)"\033]7501;");
    out_str_nf(body);
    out_str_nf((char_u *)"\033\\");
}

/*
 * Send one root record for the editor, only when it changed.
 */
    void
program_status_sync(void)
{
    garray_T	ga;
    char_u	title[MAXPATHL + 8];
    char_u	*name = ps_buf_name(curbuf);
    char_u	*refused = quit_refused != NULL && ps_any_modified()
							? quit_refused : NULL;

    if (exiting || is_not_a_term())
	return;

    ga_init2(&ga, 1, 200);
    if (refused != NULL)
	ga_concat(&ga, (char_u *)"state=blocked:kind=question:app=vim");
    else if (write_error != NULL)
	ga_concat(&ga, (char_u *)"state=error:app=vim");
    else
	ga_concat(&ga, (char_u *)"state=idle:app=vim");

    vim_snprintf((char *)title, sizeof(title), "%s%s",
	    name != NULL ? (char *)name : _("[No Name]"),
	    bufIsChanged(curbuf) ? " [+]" : "");
    ps_append_text(&ga, "title", title, PS_MAX_TITLE);
    if (refused != NULL || write_error != NULL)
	ps_append_text(&ga, "msg", refused != NULL ? refused : write_error,
								  PS_MAX_MSG);
    ga_append(&ga, NUL);
    if (ga.ga_data == NULL)
	return;

    if (last_body != NULL && STRCMP(ga.ga_data, last_body) == 0)
    {
	ga_clear(&ga);
	return;
    }
    ps_emit(ga.ga_data);
    vim_free(last_body);
    last_body = ga.ga_data;
}

/*
 * A quit was refused.  Only counts while a buffer is unsaved; other refusals,
 * such as more files to edit, aren't the user's to answer here.
 */
    void
program_status_quit_refused(void)
{
    garray_T	names;
    buf_T	*buf;
    int		count = 0;
    char_u	*name;
    size_t	len;

    // A failed ":wq" or ":x" already reports the write error.
    if (write_failed_now)
	return;
    ga_init2(&names, 1, 100);
    FOR_ALL_BUFFERS(buf)
	if (bufIsChanged(buf))
	{
	    if (count++ > 0)
		ga_concat(&names, (char_u *)", ");
	    name = ps_buf_name(buf);
	    ga_concat(&names, name != NULL ? name : (char_u *)_("[No Name]"));
	}
    ga_append(&names, NUL);
    if (count > 0 && names.ga_data != NULL)
    {
	len = STRLEN(names.ga_data) + 40;
	vim_free(quit_refused);
	quit_refused = alloc(len);
	if (quit_refused != NULL)
	    vim_snprintf((char *)quit_refused, len, "%d unsaved buffer%s: %s",
		    count, count == 1 ? "" : "s", (char *)names.ga_data);
    }
    ga_clear(&names);
}

/*
 * Any typed key answers a refused quit.
 */
    void
program_status_input(void)
{
    write_failed_now = FALSE;
    VIM_CLEAR(quit_refused);
}

/*
 * The last write failed with "errmsg", or succeeded when it is NULL.
 */
    void
program_status_write_result(char_u *errmsg)
{
    vim_free(write_error);
    write_error = errmsg != NULL ? vim_strsave(errmsg) : NULL;
    write_failed_now = errmsg != NULL;
}

/*
 * An empty-id clear removes every record, including a lingering error.
 */
    void
program_status_clear(void)
{
    if (last_body != NULL)
    {
	out_str_nf((char_u *)"\033]7501;state=clear\033\\");
	out_flush();
    }
    VIM_CLEAR(last_body);
    VIM_CLEAR(quit_refused);
    VIM_CLEAR(write_error);
    write_failed_now = FALSE;
}

#endif // VIM_APPLE_SANDBOX

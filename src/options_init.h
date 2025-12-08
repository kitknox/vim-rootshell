/* vi:set ts=8 sts=4 sw=4 noet:
 *
 * options_init.h: Runtime initialization of options[] for iOS
 *
 * iOS: Set options[] var pointers at runtime because TLS variable
 * addresses cannot be compile-time constants in static initializers.
 *
 * This file is included inside set_init_1() in option.c.
 * The helper function findoption_and_set_var() is defined before
 * set_init_1() in option.c.
 */

    // Global variables (not p_* prefixed)
    findoption_and_set_var("columns", (char_u *)&Columns);
    findoption_and_set_var("lines", (char_u *)&Rows);
    findoption_and_set_var("term", (char_u *)&T_NAME);
    findoption_and_set_var("ttytype", (char_u *)&T_NAME);

#ifdef FEAT_RIGHTLEFT
    findoption_and_set_var("aleph", (char_u *)&p_aleph);
    findoption_and_set_var("allowrevins", (char_u *)&p_ari);
    findoption_and_set_var("hkmap", (char_u *)&p_hkmap);
    findoption_and_set_var("hkmapp", (char_u *)&p_hkmapp);
    findoption_and_set_var("revins", (char_u *)&p_ri);
#endif

    findoption_and_set_var("ambiwidth", (char_u *)&p_ambw);

#ifdef FEAT_ARABIC
    findoption_and_set_var("arabicshape", (char_u *)&p_arshape);
    findoption_and_set_var("termbidi", (char_u *)&p_tbidi);
#endif

#ifdef FEAT_AUTOCHDIR
    findoption_and_set_var("autochdir", (char_u *)&p_acd);
#endif

#ifdef ELAPSED_FUNC
    findoption_and_set_var("autocomplete", (char_u *)&p_ac);
#endif

    findoption_and_set_var("autocompletedelay", (char_u *)&p_acl);
    findoption_and_set_var("autocompletetimeout", (char_u *)&p_act);
    findoption_and_set_var("autoindent", (char_u *)&p_ai);
    findoption_and_set_var("autoread", (char_u *)&p_ar);

#ifdef FEAT_AUTOSHELLDIR
    findoption_and_set_var("autoshelldir", (char_u *)&p_asd);
#endif

    findoption_and_set_var("autowrite", (char_u *)&p_aw);
    findoption_and_set_var("autowriteall", (char_u *)&p_awa);
    findoption_and_set_var("background", (char_u *)&p_bg);
    findoption_and_set_var("backspace", (char_u *)&p_bs);
    findoption_and_set_var("backup", (char_u *)&p_bk);
    findoption_and_set_var("backupcopy", (char_u *)&p_bkc);
    findoption_and_set_var("backupdir", (char_u *)&p_bdir);
    findoption_and_set_var("backupext", (char_u *)&p_bex);
    findoption_and_set_var("backupskip", (char_u *)&p_bsk);

#ifdef FEAT_BEVAL
    findoption_and_set_var("balloondelay", (char_u *)&p_bdlay);
#endif
#ifdef FEAT_BEVAL_GUI
    findoption_and_set_var("ballooneval", (char_u *)&p_beval);
#endif
#ifdef FEAT_BEVAL_TERM
    findoption_and_set_var("balloonevalterm", (char_u *)&p_bevalterm);
#endif
#if defined(FEAT_BEVAL) && defined(FEAT_EVAL)
    findoption_and_set_var("balloonexpr", (char_u *)&p_bexpr);
#endif

    findoption_and_set_var("belloff", (char_u *)&p_bo);
    findoption_and_set_var("binary", (char_u *)&p_bin);
    findoption_and_set_var("bomb", (char_u *)&p_bomb);

#ifdef FEAT_LINEBREAK
    findoption_and_set_var("breakat", (char_u *)&p_breakat);
    findoption_and_set_var("showbreak", (char_u *)&p_sbr);
#endif

#ifdef FEAT_BROWSE
    findoption_and_set_var("browsedir", (char_u *)&p_bsdir);
#endif

    findoption_and_set_var("bufhidden", (char_u *)&p_bh);
    findoption_and_set_var("buflisted", (char_u *)&p_bl);
    findoption_and_set_var("buftype", (char_u *)&p_bt);
    findoption_and_set_var("casemap", (char_u *)&p_cmp);
    findoption_and_set_var("cdhome", (char_u *)&p_cdh);
    findoption_and_set_var("cdpath", (char_u *)&p_cdpath);
    findoption_and_set_var("cedit", (char_u *)&p_cedit);

#if defined(FEAT_EVAL)
    findoption_and_set_var("charconvert", (char_u *)&p_ccv);
#endif

#ifdef FEAT_QUICKFIX
    findoption_and_set_var("chistory", (char_u *)&p_chi);
    findoption_and_set_var("errorfile", (char_u *)&p_ef);
    findoption_and_set_var("errorformat", (char_u *)&p_efm);
    findoption_and_set_var("grepformat", (char_u *)&p_gefm);
    findoption_and_set_var("grepprg", (char_u *)&p_gp);
    findoption_and_set_var("makeef", (char_u *)&p_mef);
    findoption_and_set_var("makeprg", (char_u *)&p_mp);
    findoption_and_set_var("shellpipe", (char_u *)&p_sp);
    findoption_and_set_var("previewheight", (char_u *)&p_pvh);
#endif

    findoption_and_set_var("cindent", (char_u *)&p_cin);
    findoption_and_set_var("cinkeys", (char_u *)&p_cink);
    findoption_and_set_var("cinoptions", (char_u *)&p_cino);
    findoption_and_set_var("cinscopedecls", (char_u *)&p_cinsd);
    findoption_and_set_var("cinwords", (char_u *)&p_cinw);

#ifdef FEAT_CLIPBOARD
    findoption_and_set_var("clipboard", (char_u *)&p_cb);
    findoption_and_set_var("clipmethod", (char_u *)&p_cpm);
#endif

    findoption_and_set_var("cmdheight", (char_u *)&p_ch);
    findoption_and_set_var("cmdwinheight", (char_u *)&p_cwh);
    findoption_and_set_var("comments", (char_u *)&p_com);
    findoption_and_set_var("commentstring", (char_u *)&p_cms);
    findoption_and_set_var("compatible", (char_u *)&p_cp);
    findoption_and_set_var("complete", (char_u *)&p_cpt);

#ifdef FEAT_COMPL_FUNC
    findoption_and_set_var("completefunc", (char_u *)&p_cfu);
    findoption_and_set_var("omnifunc", (char_u *)&p_ofu);
    findoption_and_set_var("thesaurusfunc", (char_u *)&p_tsrfu);
#endif

    findoption_and_set_var("completefuzzycollect", (char_u *)&p_cfc);
    findoption_and_set_var("completeitemalign", (char_u *)&p_cia);
    findoption_and_set_var("completeopt", (char_u *)&p_cot);

#if defined(FEAT_PROP_POPUP) && defined(FEAT_QUICKFIX)
    findoption_and_set_var("completepopup", (char_u *)&p_cpp);
#endif

#if defined(BACKSLASH_IN_FILENAME)
    findoption_and_set_var("completeslash", (char_u *)&p_csl);
#endif

    findoption_and_set_var("completetimeout", (char_u *)&p_cto);

#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
    findoption_and_set_var("confirm", (char_u *)&p_confirm);
#endif

    findoption_and_set_var("copyindent", (char_u *)&p_ci);
    findoption_and_set_var("cpoptions", (char_u *)&p_cpo);

#ifdef FEAT_CRYPT
    findoption_and_set_var("cryptmethod", (char_u *)&p_cm);
    findoption_and_set_var("key", (char_u *)&p_key);
#endif

#ifdef FEAT_CSCOPE
    findoption_and_set_var("cscopepathcomp", (char_u *)&p_cspc);
    findoption_and_set_var("cscopeprg", (char_u *)&p_csprg);
    findoption_and_set_var("cscoperelative", (char_u *)&p_csre);
    findoption_and_set_var("cscopetag", (char_u *)&p_cst);
    findoption_and_set_var("cscopetagorder", (char_u *)&p_csto);
    findoption_and_set_var("cscopeverbose", (char_u *)&p_csverbose);
# ifdef FEAT_QUICKFIX
    findoption_and_set_var("cscopequickfix", (char_u *)&p_csqf);
# endif
#endif

    findoption_and_set_var("debug", (char_u *)&p_debug);

#ifdef FEAT_FIND_ID
    findoption_and_set_var("define", (char_u *)&p_def);
    findoption_and_set_var("include", (char_u *)&p_inc);
# ifdef FEAT_EVAL
    findoption_and_set_var("includeexpr", (char_u *)&p_inex);
# endif
#endif

    findoption_and_set_var("delcombine", (char_u *)&p_deco);
    findoption_and_set_var("dictionary", (char_u *)&p_dict);

#ifdef FEAT_DIFF
    findoption_and_set_var("diffanchors", (char_u *)&p_dia);
    findoption_and_set_var("diffopt", (char_u *)&p_dip);
# ifdef FEAT_EVAL
    findoption_and_set_var("diffexpr", (char_u *)&p_dex);
    findoption_and_set_var("patchexpr", (char_u *)&p_pex);
# endif
#endif

#ifdef FEAT_DIGRAPHS
    findoption_and_set_var("digraph", (char_u *)&p_dg);
#endif

    findoption_and_set_var("directory", (char_u *)&p_dir);
    findoption_and_set_var("display", (char_u *)&p_dy);
    findoption_and_set_var("eadirection", (char_u *)&p_ead);
    findoption_and_set_var("edcompatible", (char_u *)&p_ed);
    findoption_and_set_var("emoji", (char_u *)&p_emoji);
    findoption_and_set_var("encoding", (char_u *)&p_enc);
    findoption_and_set_var("endoffile", (char_u *)&p_eof);
    findoption_and_set_var("endofline", (char_u *)&p_eol);
    findoption_and_set_var("equalalways", (char_u *)&p_ea);
    findoption_and_set_var("equalprg", (char_u *)&p_ep);
    findoption_and_set_var("errorbells", (char_u *)&p_eb);
    findoption_and_set_var("esckeys", (char_u *)&p_ek);
    findoption_and_set_var("eventignore", (char_u *)&p_ei);
    findoption_and_set_var("expandtab", (char_u *)&p_et);
    findoption_and_set_var("exrc", (char_u *)&p_exrc);
    findoption_and_set_var("fileencoding", (char_u *)&p_fenc);
    findoption_and_set_var("fileencodings", (char_u *)&p_fencs);
    findoption_and_set_var("fileformat", (char_u *)&p_ff);
    findoption_and_set_var("fileformats", (char_u *)&p_ffs);
    findoption_and_set_var("fileignorecase", (char_u *)&p_fic);
    findoption_and_set_var("filetype", (char_u *)&p_ft);
    findoption_and_set_var("fillchars", (char_u *)&p_fcs);

#ifdef FEAT_EVAL
    findoption_and_set_var("findfunc", (char_u *)&p_ffu);
    findoption_and_set_var("formatexpr", (char_u *)&p_fex);
    findoption_and_set_var("indentexpr", (char_u *)&p_inde);
    findoption_and_set_var("indentkeys", (char_u *)&p_indk);
    findoption_and_set_var("operatorfunc", (char_u *)&p_opfunc);
    findoption_and_set_var("tagfunc", (char_u *)&p_tfu);
    findoption_and_set_var("maxfuncdepth", (char_u *)&p_mfd);
#endif

    findoption_and_set_var("fixendofline", (char_u *)&p_fixeol);

#ifdef FEAT_FOLDING
    findoption_and_set_var("foldclose", (char_u *)&p_fcl);
    findoption_and_set_var("foldlevelstart", (char_u *)&p_fdls);
    findoption_and_set_var("foldopen", (char_u *)&p_fdo);
#endif

    findoption_and_set_var("formatlistpat", (char_u *)&p_flp);
    findoption_and_set_var("formatoptions", (char_u *)&p_fo);
    findoption_and_set_var("formatprg", (char_u *)&p_fp);

#if defined(HAVE_FSYNC)
    findoption_and_set_var("fsync", (char_u *)&p_fs);
#endif

    findoption_and_set_var("gdefault", (char_u *)&p_gd);

#if defined(CURSOR_SHAPE)
    findoption_and_set_var("guicursor", (char_u *)&p_guicursor);
#endif

#ifdef FEAT_GUI
    findoption_and_set_var("guifont", (char_u *)&p_guifont);
    findoption_and_set_var("guioptions", (char_u *)&p_go);
    findoption_and_set_var("guipty", (char_u *)&p_guipty);
    findoption_and_set_var("linespace", (char_u *)&p_linespace);
    findoption_and_set_var("mousefocus", (char_u *)&p_mousef);
    findoption_and_set_var("mousehide", (char_u *)&p_mh);
    findoption_and_set_var("mousemoveevent", (char_u *)&p_mousemev);
# if defined(FEAT_XFONTSET)
    findoption_and_set_var("guifontset", (char_u *)&p_guifontset);
# endif
    findoption_and_set_var("guifontwide", (char_u *)&p_guifontwide);
# if defined(FEAT_GUI_GTK) || defined(FEAT_GUI_X11)
    findoption_and_set_var("guiheadroom", (char_u *)&p_ghr);
# endif
# if defined(FEAT_GUI_GTK) || defined(FEAT_GUI_MSWIN)
    findoption_and_set_var("guiligatures", (char_u *)&p_guiligatures);
# endif
# ifdef FEAT_GUI_TABLINE
    findoption_and_set_var("guitablabel", (char_u *)&p_gtl);
    findoption_and_set_var("guitabtooltip", (char_u *)&p_gtt);
# endif
#endif

    findoption_and_set_var("helpfile", (char_u *)&p_hf);
    findoption_and_set_var("helpheight", (char_u *)&p_hh);

#ifdef FEAT_MULTI_LANG
    findoption_and_set_var("helplang", (char_u *)&p_hlg);
#endif

    findoption_and_set_var("hidden", (char_u *)&p_hid);
    findoption_and_set_var("highlight", (char_u *)&p_hl);
    findoption_and_set_var("history", (char_u *)&p_hi);

#if defined(FEAT_SEARCH_EXTRA)
    findoption_and_set_var("hlsearch", (char_u *)&p_hls);
#endif

    findoption_and_set_var("icon", (char_u *)&p_icon);
    findoption_and_set_var("iconstring", (char_u *)&p_iconstring);
    findoption_and_set_var("ignorecase", (char_u *)&p_ic);

#if defined(FEAT_EVAL) && (defined(FEAT_XIM) || defined(IME_WITHOUT_XIM) || defined(VIMDLL))
    findoption_and_set_var("imactivatefunc", (char_u *)&p_imaf);
    findoption_and_set_var("imstatusfunc", (char_u *)&p_imsf);
#endif

#if defined(FEAT_XIM) && defined(FEAT_GUI_GTK)
    findoption_and_set_var("imactivatekey", (char_u *)&p_imak);
    findoption_and_set_var("imstyle", (char_u *)&p_imst);
#endif

    findoption_and_set_var("imcmdline", (char_u *)&p_imcmdline);

#if defined(HAVE_INPUT_METHOD)
    findoption_and_set_var("imdisable", (char_u *)&p_imdisable);
#endif

    findoption_and_set_var("iminsert", (char_u *)&p_iminsert);
    findoption_and_set_var("imsearch", (char_u *)&p_imsearch);
    findoption_and_set_var("incsearch", (char_u *)&p_is);
    findoption_and_set_var("infercase", (char_u *)&p_inf);
    findoption_and_set_var("insertmode", (char_u *)&p_im);
    findoption_and_set_var("isfname", (char_u *)&p_isf);
    findoption_and_set_var("isident", (char_u *)&p_isi);
    findoption_and_set_var("iskeyword", (char_u *)&p_isk);
    findoption_and_set_var("isprint", (char_u *)&p_isp);
    findoption_and_set_var("joinspaces", (char_u *)&p_js);
    findoption_and_set_var("jumpoptions", (char_u *)&p_jop);

#ifdef FEAT_KEYMAP
    findoption_and_set_var("keymap", (char_u *)&p_keymap);
#endif

    findoption_and_set_var("keymodel", (char_u *)&p_km);
    findoption_and_set_var("keyprotocol", (char_u *)&p_kpc);
    findoption_and_set_var("keywordprg", (char_u *)&p_kp);

#ifdef FEAT_LANGMAP
    findoption_and_set_var("langmap", (char_u *)&p_langmap);
    findoption_and_set_var("langnoremap", (char_u *)&p_lnr);
    findoption_and_set_var("langremap", (char_u *)&p_lrm);
#endif

#if defined(FEAT_MENU) && defined(FEAT_MULTI_LANG)
    findoption_and_set_var("langmenu", (char_u *)&p_lm);
#endif

    findoption_and_set_var("laststatus", (char_u *)&p_ls);
    findoption_and_set_var("lazyredraw", (char_u *)&p_lz);
    findoption_and_set_var("lisp", (char_u *)&p_lisp);
    findoption_and_set_var("lispoptions", (char_u *)&p_lop);
    findoption_and_set_var("lispwords", (char_u *)&p_lispwords);
    findoption_and_set_var("listchars", (char_u *)&p_lcs);
    findoption_and_set_var("loadplugins", (char_u *)&p_lpl);

#if defined(DYNAMIC_LUA)
    findoption_and_set_var("luadll", (char_u *)&p_luadll);
#endif

    findoption_and_set_var("magic", (char_u *)&p_magic);
    findoption_and_set_var("makeencoding", (char_u *)&p_menc);
    findoption_and_set_var("matchpairs", (char_u *)&p_mps);
    findoption_and_set_var("matchtime", (char_u *)&p_mat);
    findoption_and_set_var("maxcombine", (char_u *)&p_mco);
    findoption_and_set_var("maxmapdepth", (char_u *)&p_mmd);
    findoption_and_set_var("maxmem", (char_u *)&p_mm);
    findoption_and_set_var("maxmempattern", (char_u *)&p_mmp);
    findoption_and_set_var("maxmemtot", (char_u *)&p_mmt);
    findoption_and_set_var("maxsearchcount", (char_u *)&p_msc);

#ifdef FEAT_MENU
    findoption_and_set_var("menuitems", (char_u *)&p_mis);
#endif

    findoption_and_set_var("messagesopt", (char_u *)&p_mopt);

#ifdef FEAT_SPELL
    findoption_and_set_var("mkspellmem", (char_u *)&p_msm);
    findoption_and_set_var("spellcapcheck", (char_u *)&p_spc);
    findoption_and_set_var("spellfile", (char_u *)&p_spf);
    findoption_and_set_var("spelllang", (char_u *)&p_spl);
    findoption_and_set_var("spelloptions", (char_u *)&p_spo);
    findoption_and_set_var("spellsuggest", (char_u *)&p_sps);
#endif

    findoption_and_set_var("modeline", (char_u *)&p_ml);
    findoption_and_set_var("modelineexpr", (char_u *)&p_mle);
    findoption_and_set_var("modelines", (char_u *)&p_mls);
    findoption_and_set_var("modifiable", (char_u *)&p_ma);
    findoption_and_set_var("modified", (char_u *)&p_mod);
    findoption_and_set_var("more", (char_u *)&p_more);
    findoption_and_set_var("mouse", (char_u *)&p_mouse);
    findoption_and_set_var("mousemodel", (char_u *)&p_mousem);

#ifdef FEAT_MOUSESHAPE
    findoption_and_set_var("mouseshape", (char_u *)&p_mouseshape);
#endif

    findoption_and_set_var("mousetime", (char_u *)&p_mouset);

#ifdef FEAT_MZSCHEME
    findoption_and_set_var("mzquantum", (char_u *)&p_mzq);
#endif
#if defined(DYNAMIC_MZSCHEME)
    findoption_and_set_var("mzschemedll", (char_u *)&p_mzschemedll);
    findoption_and_set_var("mzschemegcdll", (char_u *)&p_mzschemegcdll);
#endif

    findoption_and_set_var("nrformats", (char_u *)&p_nf);
    findoption_and_set_var("osctimeoutlen", (char_u *)&p_ost);
    findoption_and_set_var("packpath", (char_u *)&p_pp);
    findoption_and_set_var("paragraphs", (char_u *)&p_para);
    findoption_and_set_var("paste", (char_u *)&p_paste);
    findoption_and_set_var("pastetoggle", (char_u *)&p_pt);
    findoption_and_set_var("patchmode", (char_u *)&p_pm);
    findoption_and_set_var("path", (char_u *)&p_path);

#if defined(DYNAMIC_PERL)
    findoption_and_set_var("perldll", (char_u *)&p_perldll);
#endif

    findoption_and_set_var("preserveindent", (char_u *)&p_pi);

#ifdef FEAT_PROP_POPUP
    findoption_and_set_var("previewpopup", (char_u *)&p_pvp);
#endif

#ifdef FEAT_PRINTER
    findoption_and_set_var("printdevice", (char_u *)&p_pdev);
    findoption_and_set_var("printfont", (char_u *)&p_pfn);
    findoption_and_set_var("printheader", (char_u *)&p_header);
    findoption_and_set_var("printoptions", (char_u *)&p_popt);
#endif

#ifdef FEAT_POSTSCRIPT
    findoption_and_set_var("printencoding", (char_u *)&p_penc);
    findoption_and_set_var("printexpr", (char_u *)&p_pexpr);
    findoption_and_set_var("printmbcharset", (char_u *)&p_pmcs);
    findoption_and_set_var("printmbfont", (char_u *)&p_pmfn);
#endif

    findoption_and_set_var("prompt", (char_u *)&p_prompt);
    findoption_and_set_var("pumborder", (char_u *)&p_pb);
    findoption_and_set_var("pumheight", (char_u *)&p_ph);
    findoption_and_set_var("pummaxwidth", (char_u *)&p_pmw);
    findoption_and_set_var("pumwidth", (char_u *)&p_pw);

#if defined(DYNAMIC_PYTHON)
    findoption_and_set_var("pythondll", (char_u *)&p_pydll);
#endif
#if defined(FEAT_PYTHON)
    findoption_and_set_var("pythonhome", (char_u *)&p_pyhome);
#endif
#if defined(DYNAMIC_PYTHON3)
    findoption_and_set_var("pythonthreedll", (char_u *)&p_py3dll);
#endif
#if defined(FEAT_PYTHON3)
    findoption_and_set_var("pythonthreehome", (char_u *)&p_py3home);
#endif
#if defined(FEAT_PYTHON) || defined(FEAT_PYTHON3)
    findoption_and_set_var("pyxversion", (char_u *)&p_pyx);
#endif

#if defined(FEAT_QUICKFIX) && defined(FEAT_EVAL)
    findoption_and_set_var("quickfixtextfunc", (char_u *)&p_qftf);
#endif

    findoption_and_set_var("quoteescape", (char_u *)&p_qe);
    findoption_and_set_var("readonly", (char_u *)&p_ro);

#ifdef FEAT_RELTIME
    findoption_and_set_var("redrawtime", (char_u *)&p_rdt);
#endif

    findoption_and_set_var("regexpengine", (char_u *)&p_re);
    findoption_and_set_var("remap", (char_u *)&p_remap);

#ifdef FEAT_RENDER_OPTIONS
    findoption_and_set_var("renderoptions", (char_u *)&p_rop);
#endif

    findoption_and_set_var("report", (char_u *)&p_report);

#if defined(DYNAMIC_RUBY)
    findoption_and_set_var("rubydll", (char_u *)&p_rubydll);
#endif

    findoption_and_set_var("ruler", (char_u *)&p_ru);

#ifdef FEAT_STL_OPT
    findoption_and_set_var("rulerformat", (char_u *)&p_ruf);
    findoption_and_set_var("statusline", (char_u *)&p_stl);
    findoption_and_set_var("tabline", (char_u *)&p_tal);
#endif

    findoption_and_set_var("runtimepath", (char_u *)&p_rtp);
    findoption_and_set_var("scrolljump", (char_u *)&p_sj);
    findoption_and_set_var("scrolloff", (char_u *)&p_so);
    findoption_and_set_var("scrollopt", (char_u *)&p_sbo);
    findoption_and_set_var("sections", (char_u *)&p_sections);
    findoption_and_set_var("secure", (char_u *)&p_secure);
    findoption_and_set_var("selection", (char_u *)&p_sel);
    findoption_and_set_var("selectmode", (char_u *)&p_slm);

#ifdef FEAT_SESSION
    findoption_and_set_var("sessionoptions", (char_u *)&p_ssop);
    findoption_and_set_var("viewdir", (char_u *)&p_vdir);
    findoption_and_set_var("viewoptions", (char_u *)&p_vop);
#endif

    findoption_and_set_var("shell", (char_u *)&p_sh);
    findoption_and_set_var("shellcmdflag", (char_u *)&p_shcf);
    findoption_and_set_var("shellquote", (char_u *)&p_shq);
    findoption_and_set_var("shellredir", (char_u *)&p_srr);
    findoption_and_set_var("shelltemp", (char_u *)&p_stmp);
    findoption_and_set_var("shellxescape", (char_u *)&p_sxe);
    findoption_and_set_var("shellxquote", (char_u *)&p_sxq);
    findoption_and_set_var("shiftround", (char_u *)&p_sr);
    findoption_and_set_var("shiftwidth", (char_u *)&p_sw);
    findoption_and_set_var("shortmess", (char_u *)&p_shm);
    findoption_and_set_var("shortname", (char_u *)&p_sn);
    findoption_and_set_var("showcmd", (char_u *)&p_sc);
    findoption_and_set_var("showcmdloc", (char_u *)&p_sloc);
    findoption_and_set_var("showfulltag", (char_u *)&p_sft);
    findoption_and_set_var("showmatch", (char_u *)&p_sm);
    findoption_and_set_var("showmode", (char_u *)&p_smd);
    findoption_and_set_var("showtabline", (char_u *)&p_stal);

#if defined(FEAT_TABPANEL)
    findoption_and_set_var("showtabpanel", (char_u *)&p_stpl);
    findoption_and_set_var("tabpanel", (char_u *)&p_tpl);
    findoption_and_set_var("tabpanelopt", (char_u *)&p_tplo);
#endif

    findoption_and_set_var("sidescroll", (char_u *)&p_ss);
    findoption_and_set_var("sidescrolloff", (char_u *)&p_siso);
    findoption_and_set_var("smartcase", (char_u *)&p_scs);
    findoption_and_set_var("smartindent", (char_u *)&p_si);
    findoption_and_set_var("smarttab", (char_u *)&p_sta);
    findoption_and_set_var("softtabstop", (char_u *)&p_sts);
    findoption_and_set_var("splitbelow", (char_u *)&p_sb);
    findoption_and_set_var("splitkeep", (char_u *)&p_spk);
    findoption_and_set_var("splitright", (char_u *)&p_spr);
    findoption_and_set_var("startofline", (char_u *)&p_sol);
    findoption_and_set_var("suffixes", (char_u *)&p_su);
    findoption_and_set_var("suffixesadd", (char_u *)&p_sua);
    findoption_and_set_var("swapfile", (char_u *)&p_swf);
    findoption_and_set_var("swapsync", (char_u *)&p_sws);
    findoption_and_set_var("switchbuf", (char_u *)&p_swb);

#ifdef FEAT_SYN_HL
    findoption_and_set_var("synmaxcol", (char_u *)&p_smc);
    findoption_and_set_var("syntax", (char_u *)&p_syn);
#endif

    findoption_and_set_var("tabclose", (char_u *)&p_tcl);
    findoption_and_set_var("tabpagemax", (char_u *)&p_tpm);
    findoption_and_set_var("tabstop", (char_u *)&p_ts);
    findoption_and_set_var("tagbsearch", (char_u *)&p_tbs);
    findoption_and_set_var("tagcase", (char_u *)&p_tc);
    findoption_and_set_var("taglength", (char_u *)&p_tl);
    findoption_and_set_var("tagrelative", (char_u *)&p_tr);
    findoption_and_set_var("tags", (char_u *)&p_tags);
    findoption_and_set_var("tagstack", (char_u *)&p_tgst);

#if defined(DYNAMIC_TCL)
    findoption_and_set_var("tcldll", (char_u *)&p_tcldll);
#endif

    findoption_and_set_var("termencoding", (char_u *)&p_tenc);

#ifdef FEAT_TERMGUICOLORS
    findoption_and_set_var("termguicolors", (char_u *)&p_tgc);
#endif

#ifdef FEAT_TERMINAL
    findoption_and_set_var("termwinscroll", (char_u *)&p_twsl);
# if defined(MSWIN)
    findoption_and_set_var("termwintype", (char_u *)&p_twt);
# endif
#endif

    findoption_and_set_var("terse", (char_u *)&p_terse);
    findoption_and_set_var("textauto", (char_u *)&p_ta);
    findoption_and_set_var("textmode", (char_u *)&p_tx);
    findoption_and_set_var("textwidth", (char_u *)&p_tw);
    findoption_and_set_var("thesaurus", (char_u *)&p_tsr);
    findoption_and_set_var("tildeop", (char_u *)&p_to);
    findoption_and_set_var("timeout", (char_u *)&p_timeout);
    findoption_and_set_var("timeoutlen", (char_u *)&p_tm);
    findoption_and_set_var("title", (char_u *)&p_title);
    findoption_and_set_var("titlelen", (char_u *)&p_titlelen);
    findoption_and_set_var("titleold", (char_u *)&p_titleold);
    findoption_and_set_var("titlestring", (char_u *)&p_titlestring);

#if defined(FEAT_TOOLBAR) && !defined(FEAT_GUI_MSWIN)
    findoption_and_set_var("toolbar", (char_u *)&p_toolbar);
#endif
#if defined(FEAT_TOOLBAR) && defined(FEAT_GUI_GTK)
    findoption_and_set_var("toolbariconsize", (char_u *)&p_tbis);
#endif

    findoption_and_set_var("ttimeout", (char_u *)&p_ttimeout);
    findoption_and_set_var("ttimeoutlen", (char_u *)&p_ttm);
    findoption_and_set_var("ttybuiltin", (char_u *)&p_tbi);
    findoption_and_set_var("ttyfast", (char_u *)&p_tf);

#if defined(UNIX) || defined(VMS)
    findoption_and_set_var("ttymouse", (char_u *)&p_ttym);
#endif

    findoption_and_set_var("ttyscroll", (char_u *)&p_ttyscroll);

#ifdef FEAT_PERSISTENT_UNDO
    findoption_and_set_var("undodir", (char_u *)&p_udir);
    findoption_and_set_var("undofile", (char_u *)&p_udf);
#endif

    findoption_and_set_var("undolevels", (char_u *)&p_ul);
    findoption_and_set_var("undoreload", (char_u *)&p_ur);
    findoption_and_set_var("updatecount", (char_u *)&p_uc);
    findoption_and_set_var("updatetime", (char_u *)&p_ut);

#ifdef FEAT_VARTABS
    findoption_and_set_var("varsofttabstop", (char_u *)&p_vsts);
    findoption_and_set_var("vartabstop", (char_u *)&p_vts);
#endif

    findoption_and_set_var("verbose", (char_u *)&p_verbose);
    findoption_and_set_var("verbosefile", (char_u *)&p_vfile);

#ifdef FEAT_VIMINFO
    findoption_and_set_var("viminfo", (char_u *)&p_viminfo);
    findoption_and_set_var("viminfofile", (char_u *)&p_viminfofile);
#endif

    findoption_and_set_var("virtualedit", (char_u *)&p_ve);
    findoption_and_set_var("visualbell", (char_u *)&p_vb);
    findoption_and_set_var("warn", (char_u *)&p_warn);
    findoption_and_set_var("weirdinvert", (char_u *)&p_wiv);
    findoption_and_set_var("whichwrap", (char_u *)&p_ww);
    findoption_and_set_var("wildchar", (char_u *)&p_wc);
    findoption_and_set_var("wildcharm", (char_u *)&p_wcm);
    findoption_and_set_var("wildignore", (char_u *)&p_wig);
    findoption_and_set_var("wildignorecase", (char_u *)&p_wic);
    findoption_and_set_var("wildmenu", (char_u *)&p_wmnu);
    findoption_and_set_var("wildmode", (char_u *)&p_wim);
    findoption_and_set_var("wildoptions", (char_u *)&p_wop);

#ifdef FEAT_WAK
    findoption_and_set_var("winaltkeys", (char_u *)&p_wak);
#endif

    findoption_and_set_var("window", (char_u *)&p_window);
    findoption_and_set_var("winheight", (char_u *)&p_wh);
    findoption_and_set_var("winminheight", (char_u *)&p_wmh);
    findoption_and_set_var("winminwidth", (char_u *)&p_wmw);
    findoption_and_set_var("winwidth", (char_u *)&p_wiw);

#ifdef FEAT_WAYLAND
    findoption_and_set_var("wlseat", (char_u *)&p_wse);
    findoption_and_set_var("wltimeoutlen", (char_u *)&p_wtm);
# ifdef FEAT_WAYLAND_CLIPBOARD_FS
    findoption_and_set_var("wlsteal", (char_u *)&p_wst);
# endif
#endif

    findoption_and_set_var("wrapmargin", (char_u *)&p_wm);
    findoption_and_set_var("wrapscan", (char_u *)&p_ws);
    findoption_and_set_var("write", (char_u *)&p_write);
    findoption_and_set_var("writeany", (char_u *)&p_wa);
    findoption_and_set_var("writebackup", (char_u *)&p_wb);
    findoption_and_set_var("writedelay", (char_u *)&p_wd);
    findoption_and_set_var("xtermcodes", (char_u *)&p_xtermcodes);

#!/usr/bin/env python3
import subprocess
import os

old_dir = "/Users/kit/Development/vim_ios/src"
new_dir = "/Users/kit/Development/vim9_ios/src"

files = [
    "arabic.c", "autocmd.c", "blowfish.c", "buffer.c", "change.c", "channel.c",
    "charset.c", "cindent.c", "cmdexpand.c", "cmdhist.c", "crypt.c", "crypt_zip.c",
    "debugger.c", "dict.c", "diff.c", "digraph.c", "drawline.c", "drawscreen.c",
    "edit.c", "eval.c", "evalfunc.c", "evalvars.c", "ex_cmds.c", "ex_cmds2.c",
    "ex_docmd.c", "ex_eval.c", "ex_getln.c", "fileio.c", "filepath.c", "findfile.c",
    "fold.c", "getchar.c", "hardcopy.c", "highlight.c", "indent.c", "insexpand.c",
    "list.c", "main.c", "map.c", "mark.c", "mbyte.c", "memfile.c", "memline.c",
    "menu.c", "message.c", "misc1.c", "misc2.c", "mouse.c", "normal.c", "ops.c",
    "option.c", "optionstr.c", "os_unix.c", "popupmenu.c", "popupwin.c", "profiler.c",
    "quickfix.c", "regexp.c", "regexp_nfa.c", "register.c", "screen.c", "scriptfile.c",
    "search.c", "sign.c", "spell.c", "spellfile.c", "spellsuggest.c", "syntax.c",
    "tag.c", "term.c", "textprop.c", "ui.c", "undo.c", "usercmd.c", "userfunc.c",
    "viminfo.c", "window.c"
]

def count_tls(filepath):
    try:
        with open(filepath, 'r') as f:
            return f.read().count("static __thread")
    except:
        return 0

results = []
for f in files:
    old_path = os.path.join(old_dir, f)
    new_path = os.path.join(new_dir, f)
    old_count = count_tls(old_path)
    new_count = count_tls(new_path)
    if old_count > new_count:
        results.append((f, old_count, new_count, old_count - new_count))

results.sort(key=lambda x: x[3], reverse=True)
print("=== Files needing TLS additions (sorted by missing count) ===")
for f, old, new, missing in results:
    print(f"{f}: old={old} new={new} missing={missing}")

print(f"\nTotal files needing work: {len(results)}")
print(f"Total missing TLS markers: {sum(r[3] for r in results)}")

# Vim 9.2 Apple-platform port

This is the rootshell-maintained fork of Vim 9.2. It builds Vim and xxd as
dynamic XCFrameworks for iOS, iOS Simulator, Mac Catalyst, and visionOS using
the `ios_system` framework. The Swift package is distributed from
`kitknox/vim-rootshell` and is versioned independently from upstream Vim.

## Building

### Prerequisites

1. A current Xcode installation with the iOS and visionOS SDKs
2. A sibling `ios_system` checkout with its Apple XCFrameworks already built

From the repository root, run:

```bash
swift run --package-path xcfs build
```

The build produces ignored artifacts under `.build/`:

- `vim.xcframework` and `xxd.xcframework`
- `vim.xcframework.zip` and `xxd.xcframework.zip`
- `release.md` with SwiftPM checksums and platform details

The release manifest in `Package.swift` exposes one `vim` library product that
contains both binary targets. For a release, rebuild the archives, update the
versioned GitHub URLs and checksums, validate with `swift package dump-package`,
tag the manifest commit, and attach both zip files to the matching release.

## Runtime bundle

```bash
./prepare_runtime.sh
```

This refreshes the checked-in `VimRuntime.bundle` containing syntax files,
colors, filetype plugins, autoload helpers, and Vim help. The binary Swift
package does not include this bundle. rootshell keeps its copy in application
resources and sets `VIMRUNTIME` before invoking Vim.

## Integration

See `INTEGRATION.md` for consumer instructions. rootshell uses the exact Swift
package release, links a compatible `ios_system.framework`, registers the Vim
and vi commands in `commandDictionary.plist`, and retains `VimRuntime.bundle`
as an app resource.

## Key Apple-platform adaptations

### Thread-local state

Global Vim state is made thread-local with `__thread` so multiple ios_system
sessions can run isolated Vim instances. Standard streams are provided through
the thread-local ios_system `thread_stdin`, `thread_stdout`, and
`thread_stderr` plumbing.

### Sandboxed process model

- Shell execution is routed through `ios_system()` instead of `fork()`/`exec()`.
- `EXITFREE` cleanup supports repeated in-process invocations.
- Channels, Vim's terminal feature, cscope, language interpreters, GUI, and X11
  are disabled by the XCFramework build.
- Vim's built-in terminal library is used instead of ncurses/termcap.

### Terminal behavior

- The build uses Vim's huge feature set and enables `termguicolors`.
- The cursor-position query (`KS_U7`) is enabled.
- The iOS termcap includes the Backspace key capability needed in Insert mode.
- Terminal output is flushed through the ios_system stream after writes.

## Maintenance utilities

TLS addresses are not compile-time constants, so `src/optiondefs.h` carries a
second, iOS copy of `options[]` with NULL var pointers, and `src/options_init.h`
fills them in at runtime. Both are generated from the portable table:

```bash
swift run --package-path xcfs options           # rewrite both files
swift run --package-path xcfs options --check   # exit 1 if either is stale
```

The build refuses to run while either file is stale.

The build also gates every slice:

- Writable non-TLS data (`__DATA,__data`, `__bss`, `__common`) in `vim` or
  `xxd` must be listed in `xcfs/shared-data.allowlist`. A new symbol there is
  state shared between concurrent Vim sessions: mark it `__thread`, or
  allowlist it only if it is read-only after load (such as tables referenced
  from other static initializers, which TLS cannot hold).
- The shipped frameworks and dSYMs must not contain the build machine's home
  path, user name, or host names. `pathdef.c` is sanitized, DWARF paths are
  remapped, and the binaries are stripped of their debug map.

## Upstream merges

1. `git merge --no-commit vX.Y.Z` from the `upstream` remote (vim/vim); keep
   `.github/dependabot.yml` deleted.
2. Most conflicts are `static` lines the fork marked `static __thread`: take
   upstream's line and re-add `__thread`.
3. `swift run --package-path xcfs options`, then add new `EXTERN` globals from
   `src/globals.h` to `src/globals_init.h`.
4. Build. The shared-data gate lists every new static that needs `__thread`.
5. Review new code for fork/exec, signals, raw fds 0/1/2, `ioctl`, and
   process-wide state; route them through ios_system or guard them with
   `VIM_APPLE_SANDBOX`.
6. `./prepare_runtime.sh`, and check that bundled scripts' autoload and
   `import` targets are present.

## Supported slices

- iOS arm64 device
- iOS Simulator arm64
- Mac Catalyst arm64 and x86_64
- visionOS arm64 device
- visionOS Simulator arm64

## Current source baseline

The fork is based on Vim 9.2.1252 plus rootshell's Apple-platform integration
changes. The build uses the huge feature set without Lua or Python interpreters.

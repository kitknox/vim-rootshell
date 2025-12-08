# Vim 9.1 iOS Port

This is a port of Vim 9.1 for iOS, iOS Simulator, Mac Catalyst, and visionOS, designed to work with the ios_system framework.

## Building

### Prerequisites

1. Xcode with iOS/visionOS SDKs
2. ios_system framework built at `../ios_system/.build/`

### Build XCFramework

```bash
# From vim9_ios root directory
swift run --package-path xcfs build
```

This creates:
- `.build/vim.xcframework` - Vim framework for all platforms
- `.build/xxd.xcframework` - xxd hex dump utility
- `.build/vim.xcframework.zip` - Release archive with checksum

### Create Runtime Bundle

```bash
./prepare_runtime.sh
```

Creates `VimRuntime.bundle` (~2.5MB) with syntax highlighting, colorschemes, and ftplugin files.

## Integration

See `INTEGRATION.md` for detailed integration instructions.

### Quick Start

1. Add `vim.xcframework` and `xxd.xcframework` to your Xcode project
2. Add `VimRuntime.bundle` to your app's resources
3. Before launching vim, set environment:

```swift
if let bundlePath = Bundle.main.path(forResource: "VimRuntime", ofType: "bundle") {
    setenv("VIMRUNTIME", "\(bundlePath)/Contents/Resources/vim", 1)
}
setenv("TERM", "xterm-256color", 1)
```

## Key iOS Adaptations

### Thread-Local Storage (TLS)

All global variables use `__thread` for thread-local storage, enabling multiple concurrent vim instances:

- `#define EXTERN __thread` in main.c
- Static variables in key files marked with `__thread`

### ios_system Integration

- System calls redirected via `ios_error.h` macros
- Uses `ios_system()` instead of `fork()`/`exec()`
- Thread-safe I/O via `thread_stdin`, `thread_stdout`, `thread_stderr`

### Terminal Fixes

- KS_U7 (cursor position query) disabled to prevent hangs
- FEAT_TERMGUICOLORS disabled on iOS/visionOS (no X11)
- System termcap.h excluded to avoid conflicts

## Supported Platforms

- iOS arm64 (device)
- iOS Simulator arm64
- Mac Catalyst arm64 + x86_64
- visionOS arm64
- visionOS Simulator arm64

## Features

- **Enabled**: Syntax highlighting, big feature set, ncurses
- **Disabled**: Lua interpreter, Python interpreter, GUI, X11

## File Structure

```
vim9_ios/
├── src/                    # Vim source with iOS modifications
│   ├── ios_error.h         # ios_system integration header
│   ├── main.c              # EXTERN __thread, TLS statics
│   ├── vim.h               # TargetConditionals.h include
│   ├── os_unix.c           # ios_system includes and defines
│   ├── term.c              # KS_U7 disable, termcap.h fix
│   └── feature.h           # FEAT_TERMGUICOLORS conditional
├── xcfs/                   # Swift build tool
├── runtime/                # Vim runtime files
├── Package.swift           # Swift package definition
├── prepare_runtime.sh      # Runtime bundle creator
└── VimRuntime.bundle/      # Generated runtime bundle
```

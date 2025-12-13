# Vim iOS Integration Guide

This guide explains how to integrate Vim 9.1 into an iOS/macOS Catalyst/visionOS app using the ios_system framework.

## Prerequisites

- ios_system framework built and available
- Vim xcframeworks built via `swift run --package-path xcfs build`
- VimRuntime.bundle created via `./prepare_runtime.sh`

## Step 1: Add Frameworks to Xcode Project

1. Drag `vim.xcframework` and `xxd.xcframework` into your project
2. Ensure they are set to "Embed & Sign" in target settings
3. Add `VimRuntime.bundle` to your app's resources (Copy Bundle Resources)

## Step 2: Configure Command Dictionary

Add vim commands to your app's `extraCommandsDictionary.plist`:

```xml
<key>vim</key>
<array>
    <string>vim.framework/vim</string>
    <string>vim_main</string>
    <string>-</string>
    <string>file</string>
</array>
<key>vi</key>
<array>
    <string>vim.framework/vim</string>
    <string>vim_main</string>
    <string>-</string>
    <string>file</string>
</array>
<key>view</key>
<array>
    <string>vim.framework/vim</string>
    <string>vim_main</string>
    <string>-</string>
    <string>file</string>
</array>
<key>xxd</key>
<array>
    <string>xxd.framework/xxd</string>
    <string>xxd_main</string>
    <string>-</string>
    <string>file</string>
</array>
```

## Step 3: Set Environment Variables

Before invoking vim, configure the environment:

```swift
import ios_system

func setupVimEnvironment() {
    // Set VIMRUNTIME to point to bundled runtime files
    if let bundlePath = Bundle.main.path(forResource: "VimRuntime", ofType: "bundle") {
        ios_setenv("VIMRUNTIME", "\(bundlePath)/Contents/Resources/vim", 1)
    }

    // Set terminal type
    ios_setenv("TERM", "xterm-256color", 1)

    // Optional: Set home directory for .vimrc
    if let docsPath = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first {
        ios_setenv("HOME", docsPath.path, 1)
    }
}
```

## Step 4: Execute Vim

Use ios_system to run vim:

```swift
// Synchronous execution
let result = ios_system("vim filename.txt")

// Or with async support
let command = ios_system_async("vim filename.txt", options)
```

## Thread Safety

This vim port supports multiple concurrent instances through thread-local storage:

- Each vim instance runs in its own thread
- Global state is isolated via `__thread` variables
- I/O streams are thread-local (`thread_stdin`, `thread_stdout`, `thread_stderr`)

### Running Multiple Instances

```swift
// Instance 1 in thread A
DispatchQueue.global().async {
    ios_system("vim file1.txt")
}

// Instance 2 in thread B
DispatchQueue.global().async {
    ios_system("vim file2.txt")
}
```

## Terminal Requirements

Vim expects a terminal emulator that supports:

- ANSI escape sequences
- xterm-256color capabilities
- Proper stdin/stdout/stderr handling

Set up I/O streams before execution:

```swift
ios_setStreams(inputPipe.fileHandleForReading,
               outputPipe.fileHandleForWriting,
               errorPipe.fileHandleForWriting)
```

## Filesystem Constraints

iOS apps can only write to:

- `~/Documents/` - User documents
- `~/Library/` - App data
- `~/tmp/` - Temporary files

Configure vim to use these paths:

```vim
" In .vimrc
set directory=~/tmp//
set backupdir=~/tmp//
set undodir=~/Library/vim/undo//
```

## Sandboxed Process APIs

The App Store sandbox does not allow spawning arbitrary processes. This port:

- Uses `ios_system()` for `:!`, `system()` and related shell execution
- Disables fork/exec-based features (e.g. `job_start()`, channels, NetBeans integration)
- Enables Vim's `EXITFREE` cleanup to avoid leaking state across repeated in-process runs

## Troubleshooting

### Vim hangs on startup

The KS_U7 cursor position query has been disabled, but if hangs occur:

1. Ensure TERM is set correctly
2. Check that terminal emulator handles all escape sequences
3. Verify ios_system streams are properly configured

### Syntax highlighting not working

1. Verify VIMRUNTIME points to valid bundle path
2. Check that VimRuntime.bundle contains syntax/ directory
3. Run `:scriptnames` in vim to see loaded files

### Colors not displaying

1. Ensure TERM=xterm-256color
2. FEAT_TERMGUICOLORS is disabled on iOS; use 256-color themes
3. Check terminal emulator color support

## VimRuntime.bundle Contents

The runtime bundle includes:

- **syntax/**: 45+ language syntax definitions
- **colors/**: 20+ color schemes
- **ftplugin/**: Language-specific plugins
- **indent/**: Indentation rules
- **autoload/**: Netrw file browser, utilities
- **plugin/**: matchparen, netrwPlugin

## Building from Source

```bash
# Build xcframeworks
swift run --package-path xcfs build

# Create runtime bundle
./prepare_runtime.sh

# Output locations
ls .build/vim.xcframework
ls .build/xxd.xcframework
ls VimRuntime.bundle
```

## Version Information

- Vim version: 9.1.285
- Base: Upstream Vim 9.1 with iOS adaptations
- Features: big (no Lua/Python)

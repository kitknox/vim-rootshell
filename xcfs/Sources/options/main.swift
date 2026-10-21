// Usage from the repository root:
//   swift run --package-path xcfs options           rewrite optiondefs.h and options_init.h
//   swift run --package-path xcfs options --check   exit 1 if either is stale

import Foundation
import OptionsGen

let srcDir = URL(fileURLWithPath: FileManager.default.currentDirectoryPath).appendingPathComponent("src")
let check = CommandLine.arguments.contains("--check")

do {
    let stale = try generateOptions(srcDir: srcDir, check: check)
    if check && !stale.isEmpty {
        FileHandle.standardError.write(Data(
            "options: \(stale.joined(separator: ", ")) out of date; run `swift run --package-path xcfs options`\n".utf8))
        exit(1)
    }
    print(stale.isEmpty ? "options: up to date" : "options: wrote \(stale.joined(separator: ", "))")
} catch {
    FileHandle.standardError.write(Data("options: \(error)\n".utf8))
    exit(1)
}

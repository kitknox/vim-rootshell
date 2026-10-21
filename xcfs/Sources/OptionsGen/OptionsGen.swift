// Regenerates the iOS copy of options[] in src/optiondefs.h and src/options_init.h
// from the portable table. TLS addresses are not constant initializers, so the
// iOS table carries NULL var pointers and options_init.h fills them in at runtime.

import Foundation

public struct OptionsGenError: Error, CustomStringConvertible {
    public let description: String
}

private let declaration = "static __thread struct vimoption options[] =\n"
private let portableOpen = "#if !TARGET_OS_IPHONE\n{"
private let iosOpen = "#else // TARGET_OS_IPHONE\n// iOS: var pointers are NULL at compile time, set at runtime via options_init.h\n{"
private let iosClose = "#endif // TARGET_OS_IPHONE\n"
private let endMarker = "    // end marker\n    {NULL, NULL, 0, NULL, PV_NONE, NULL, NULL, {NULL, NULL} SCTX_INIT}\n};\n"

private let varPointer = try! NSRegularExpression(pattern: #"\(char_u \*\)&([A-Za-z_][A-Za-z0-9_]*)"#)
private let optionName = try! NSRegularExpression(pattern: #"^\s*\{"([a-z][a-z0-9]*)""#)
private let termEntry = try! NSRegularExpression(pattern: #"^\s*p_term\("(t_[^"]+)",\s*([A-Za-z_0-9]+)\)"#)

/// Returns the names of the files that were (or, with `check`, would be) rewritten.
public func generateOptions(srcDir: URL, check: Bool) throws -> [String] {
    let optiondefsURL = srcDir.appendingPathComponent("optiondefs.h")
    let optionsInitURL = srcDir.appendingPathComponent("options_init.h")

    // Vim sources are not uniformly UTF-8; Latin-1 round-trips every byte.
    guard let originalData = try? Data(contentsOf: optiondefsURL),
          let original = String(data: originalData, encoding: .isoLatin1) else {
        throw OptionsGenError(description: "cannot read \(optiondefsURL.path)")
    }

    // Accepts both the generated layout and a freshly merged upstream table.
    guard let declRange = original.range(of: declaration)
            ?? original.range(of: "static struct vimoption options[] =\n") else {
        throw OptionsGenError(description: "options[] declaration not found")
    }
    let prefix = String(original[..<declRange.lowerBound])
    var rest = original[declRange.upperBound...]
    if rest.hasPrefix(portableOpen) {
        rest = rest.dropFirst(portableOpen.count)
    } else if rest.hasPrefix("{") {
        rest = rest.dropFirst()
    } else {
        throw OptionsGenError(description: "options[] body not found")
    }
    guard let endRange = rest.range(of: endMarker) else {
        throw OptionsGenError(description: "options[] end marker not found")
    }
    let body = String(rest[..<endRange.upperBound])
    var suffix = rest[endRange.upperBound...]
    if suffix.hasPrefix("#else // TARGET_OS_IPHONE\n"), let iosEnd = suffix.range(of: iosClose) {
        suffix = suffix[iosEnd.upperBound...]
    }

    let iosBody = varPointer.stringByReplacingMatches(
        in: body, range: NSRange(body.startIndex..., in: body), withTemplate: "(char_u *)NULL")
    let optiondefs = prefix + declaration + portableOpen + body + iosOpen + iosBody + iosClose + suffix

    let outputs = [
        (optiondefsURL, optiondefs),
        (optionsInitURL, try optionsInit(body: body)),
    ]
    var stale: [String] = []
    for (url, text) in outputs {
        let data = text.data(using: .isoLatin1)!
        guard (try? Data(contentsOf: url)) != data else { continue }
        stale.append(url.lastPathComponent)
        if !check {
            try data.write(to: url)
        }
    }
    return stale
}

// Replays the table's conditionals verbatim so every assignment compiles under
// exactly the configuration its option entry does.
private func optionsInit(body: String) throws -> String {
    var lines: [String] = []
    var currentOption: String?
    // A directive continued with a trailing backslash: replayed, or skipped for #define.
    var continuation: (keep: Bool, line: String)?
    for line in body.components(separatedBy: "\n") {
        let continues = line.trimmingCharacters(in: .whitespaces).hasSuffix("\\")
        if let pending = continuation {
            if pending.keep {
                lines[lines.count - 1] += "\n" + line
            }
            continuation = continues ? pending : nil
            continue
        }
        if let name = directiveName(line) {
            let keep = name != "define" && name != "undef"
            if keep {
                lines.append(line)
            }
            continuation = continues ? (keep, line) : nil
            continue
        }
        if let term = captures(termEntry, line) {
            lines.append("    findoption_and_set_var(\"\(term[0])\", (char_u *)&\(term[1]));")
            continue
        }
        if let name = captures(optionName, line) {
            currentOption = name[0]
        }
        let range = NSRange(line.startIndex..., in: line)
        for match in varPointer.matches(in: line, range: range) {
            guard let option = currentOption else {
                throw OptionsGenError(description: "var pointer before any option: \(line)")
            }
            let variable = line[Range(match.range(at: 1), in: line)!]
            lines.append("    findoption_and_set_var(\"\(option)\", (char_u *)&\(variable));")
        }
    }

    // Drop conditionals that guard no assignment.
    var changed = true
    while changed {
        changed = false
        var out: [String] = []
        for line in lines {
            if directiveName(line) == "endif", let last = out.last, let lastName = directiveName(last) {
                if lastName.hasPrefix("if") {
                    out.removeLast()
                    changed = true
                    continue
                }
                if lastName == "else" {
                    out.removeLast()
                    changed = true
                }
            }
            out.append(line)
        }
        lines = out
    }

    return """
        /* vi:set ts=8 sts=4 sw=4 noet:
         *
         * options_init.h: Runtime initialization of options[] for iOS
         *
         * Generated by `swift run --package-path xcfs options`; do not edit.
         *
         * Included in set_init_1() and free_all_options() in option.c, where
         * findoption_and_set_var() is defined.
         */

        """ + lines.joined(separator: "\n") + "\n"
}

private func directiveName(_ line: String) -> String? {
    let trimmed = line.trimmingCharacters(in: .whitespaces)
    guard trimmed.hasPrefix("#") else { return nil }
    let rest = trimmed.dropFirst().drop(while: { $0 == " " || $0 == "\t" })
    return String(rest.prefix(while: { $0.isLetter }))
}

private func captures(_ regex: NSRegularExpression, _ line: String) -> [String]? {
    guard let m = regex.firstMatch(in: line, range: NSRange(line.startIndex..., in: line)) else { return nil }
    return (1..<m.numberOfRanges).map { String(line[Range(m.range(at: $0), in: line)!]) }
}

// swift-tools-version: 5.9

import PackageDescription

let package = Package(
    name: "vim",
    platforms: [
        .iOS(.v14),
        .macCatalyst(.v14),
        .visionOS(.v1),
    ],
    products: [
        .library(name: "vim", targets: ["vim", "xxd"]),
    ],
    targets: [
        .binaryTarget(
            name: "vim",
            url: "https://github.com/kitknox/vim-rootshell/releases/download/v0.1.1/vim.xcframework.zip",
            checksum: "a11bec68baf98be35abeca5aaabb3dbcbe783ead04316823d4ef19b9fae284e8"
        ),
        .binaryTarget(
            name: "xxd",
            url: "https://github.com/kitknox/vim-rootshell/releases/download/v0.1.1/xxd.xcframework.zip",
            checksum: "91787ae557870d6ae437e75dd4081fd10981c2552566e47fc0823934f8e0e4e2"
        ),
    ]
)

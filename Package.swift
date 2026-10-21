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
            url: "https://github.com/kitknox/vim-rootshell/releases/download/v0.2.0/vim.xcframework.zip",
            checksum: "b4bef6d5d5f938ea1061b4e00ccc531a77dc0d889c66e1a6b05704c9f41b27e4"
        ),
        .binaryTarget(
            name: "xxd",
            url: "https://github.com/kitknox/vim-rootshell/releases/download/v0.2.0/xxd.xcframework.zip",
            checksum: "f8c58447454de2bdbafdc1e4d3a40a7ddb4e159b8b3a6d1b15a4086edb88312f"
        ),
    ]
)

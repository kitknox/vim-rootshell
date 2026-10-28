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
            url: "https://github.com/kitknox/vim-rootshell/releases/download/v0.2.1/vim.xcframework.zip",
            checksum: "3bba2c101792968274824841e294df8443350bf85e13dee89a20771fd21358d6"
        ),
        .binaryTarget(
            name: "xxd",
            url: "https://github.com/kitknox/vim-rootshell/releases/download/v0.2.1/xxd.xcframework.zip",
            checksum: "d8d8b46025ca6537572e57e2968f28643ca096db725dd3379e32d4d3920127e9"
        ),
    ]
)

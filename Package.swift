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
            url: "https://github.com/kitknox/vim-rootshell/releases/download/v0.2.2/vim.xcframework.zip",
            checksum: "b49ac0ab0d388a896d3bcf27b3b3f691c2bb8fce72a8651c2eca4d5f323cd712"
        ),
        .binaryTarget(
            name: "xxd",
            url: "https://github.com/kitknox/vim-rootshell/releases/download/v0.2.2/xxd.xcframework.zip",
            checksum: "9cb457bf30f90ee41d471cf385573ac3e4f1463bec5bb471b7c6ba15bd898274"
        ),
    ]
)

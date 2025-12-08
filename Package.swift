// swift-tools-version:5.3

import PackageDescription

// For development, use local paths. For releases, update to URLs with checksums.
// To build xcframeworks: swift run --package-path xcfs build
// To create runtime bundle: ./prepare_runtime.sh

let package = Package(
    name: "vim",
    platforms: [
        .iOS(.v14),
        .macCatalyst(.v14),
    ],
    products: [
        .library(name: "vim", targets: ["vim", "xxd"])
    ],
    dependencies: [
    ],
    targets: [
        // Development: Use local xcframework paths
        .binaryTarget(
            name: "vim",
            path: ".build/vim.xcframework"
        ),
        .binaryTarget(
            name: "xxd",
            path: ".build/xxd.xcframework"
        ),

        // Release: Uncomment and update URLs/checksums for distribution
        // .binaryTarget(
        //     name: "vim",
        //     url: "https://github.com/YOUR_REPO/vim/releases/download/VERSION/vim.xcframework.zip",
        //     checksum: "CHECKSUM_HERE"
        // ),
        // .binaryTarget(
        //     name: "xxd",
        //     url: "https://github.com/YOUR_REPO/vim/releases/download/VERSION/xxd.xcframework.zip",
        //     checksum: "CHECKSUM_HERE"
        // ),
    ]
)

// swift-tools-version: 5.10
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

private func createTarget(name: String) -> Target {
    Target.binaryTarget(
        name: "\(name)",
        path: "./Sources/\(name).xcframework"
    )
}

let package = Package(
    name: "TestCreatePackage",
    products: [
        // Products define the executables and libraries a package produces, making them visible to other packages.
        .library(
            name: "TestCreatePackage",
            targets: ["TestCreatePackage"]),
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .target(
            name: "TestCreatePackage"),
        .testTarget(
            name: "TestCreatePackageTests",
            dependencies: ["TestCreatePackage"]),
        createTarget(name: "eKYCLib"),
        createTarget(name: "ICNFCCardReader"),
        createTarget(name: "ICSdkEKYC"),
        createTarget(name: "OpenSSL")
        
    ]
)

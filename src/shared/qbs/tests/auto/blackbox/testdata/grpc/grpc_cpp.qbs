import qbs

CppApplication {
    name: "grpc_cpp"
    consoleApplication: true
    condition: hasDependencies

    Depends { name: "cpp" }
    cpp.cxxLanguageVersion: "c++11"
    cpp.warningLevel: "none"

    Depends { name: "protobuf.cpp"; required: false }
    protobuf.cpp.useGrpc: true

    property bool hasDependencies: {
        console.info("has grpc: " + protobuf.cpp.present);
        return protobuf.cpp.present;
    }

    files: "grpc.cpp"

    Group {
        files: "grpc.proto"
        fileTags: "protobuf.grpc"
    }
}

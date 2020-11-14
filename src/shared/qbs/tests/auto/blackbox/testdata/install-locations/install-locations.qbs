Project {
    property bool dummy: {
        if (qbs.targetOS.contains("windows"))
            console.info("is windows");
        else if (qbs.targetOS.contains("macos"))
            console.info("is mac");
        else
            console.info("is unix");
    }
    CppApplication {
        name: "theapp"
        install: true
        files: "main.cpp"
        Group {
            fileTagsFilter: "application"
            fileTags: "some-tag"
        }
    }
    DynamicLibrary {
        name: "thelib"
        install: true
        installImportLib: true
        Depends { name: "cpp" }
        files: "thelib.cpp"
    }
}

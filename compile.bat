    # Optional, needed for the Clang Code Model if llvm-config is not in PATH:
    export LLVM_INSTALL_DIR=/path/to/llvm (or "set" on Windows)
    # Optional, disable Clang Refactoring
    export QTC_DISABLE_CLANG_REFACTORING=1
    # Optional, needed to let the QbsProjectManager plugin use system Qbs:
    export QBS_INSTALL_DIR=/path/to/qbs
    # Optional, needed for the Python enabled dumper on Windows
    set PYTHON_INSTALL_DIR=D:\Programs\Python38
    # Optional, needed to use system KSyntaxHighlighting:
    set KSYNTAXHIGHLIGHTING_LIB_DIR to folder holding the KSyntaxHighlighting library
    # if automatic deducing of include folder fails set KSYNTAXHIGHLIGHTING_INCLUDE_DIR as well
    # both variables can also be passed as qmake variables
    set SOURCE_DIRECTORY=D:\qt-creator-opensource-src-4.11.0\src

    cd $SOURCE_DIRECTORY
    qmake -r
    nmake
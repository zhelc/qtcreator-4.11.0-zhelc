rem CALL "D:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
rem set PATH=D:\Programs\Qt5.9.9\5.9.9\Src\qtbase\bin;D:\Qt-creator-build\qt5.9.9-vs13\qt-creator-opensource-src-4.11.0\bin;%PATH%
set LLVM_INSTALL_DIR=D:\Programs\LLVM
set CLANGFORMAT_LIBS=D:\Programs\LLVM\lib
set QTC_DISABLE_CLANG_REFACTORING=1
set PYTHON_INSTALL_DIR=D:\Programs\Python38
set SOURCE_DIRECTORY=D:\Qt-creator-build\qt5.9.9-vs13\qt-creator-opensource-src-4.11.0\src
cd /d ./src
qmake -r
nmake
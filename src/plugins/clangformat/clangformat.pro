message("clangformat.pro .0..................................")
include(../../qtcreatorplugin.pri)
include(clangformat-source.pri)
include(../../shared/clang/clang_installation.pri)

include(../../shared/clang/clang_defines.pri)
message("clangformat.pro .1..................................")
requires(!isEmpty(CLANGFORMAT_LIBS))
message("clangformat.pro .2..................................")
LIBS += $$CLANGFORMAT_LIBS
INCLUDEPATH += $$LLVM_INCLUDEPATH

QMAKE_CXXFLAGS_WARN_ON *= $$LLVM_CXXFLAGS_WARNINGS
QMAKE_CXXFLAGS *= $$LLVM_CXXFLAGS
unix:!macos:QMAKE_LFLAGS += -Wl,--exclude-libs,ALL
message("clangformat.pro .3..................................")
SOURCES += \
    clangformatconfigwidget.cpp \
    clangformatindenter.cpp \
    clangformatplugin.cpp \
    clangformatsettings.cpp \
    clangformatutils.cpp

HEADERS += \
    clangformatconfigwidget.h \
    clangformatindenter.h \
    clangformatplugin.h \
    clangformatsettings.h \
    clangformatutils.h

FORMS += \
    clangformatchecks.ui \
    clangformatconfigwidget.ui
message("clangformat.pro .4..................................")
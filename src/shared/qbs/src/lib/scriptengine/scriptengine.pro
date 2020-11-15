TARGET = qbsscriptengine
include(../library.pri)
INSTALLS =

QT         = core-private

DEFINES   += QT_BUILD_SCRIPT_LIB

DEFINES   += JSC=QTJSC jscyyparse=qtjscyyparse jscyylex=qtjscyylex jscyyerror=qtjscyyerror WTF=QTWTF
DEFINES   += QT_NO_USING_NAMESPACE

CONFIG += building-libs
CONFIG += staticlib

GENERATED_SOURCES_DIR = generated

CONFIG += QTDIR_build

# Disable a few warnings on Windows.
# These are in addition to the ones disabled in WebKit.pri
msvc: QMAKE_CXXFLAGS += -wd4396 -wd4099
else: QMAKE_CXXFLAGS += -Wno-deprecated

# We cannot afford -O0 for QtScript even in debug builds.
QMAKE_CXXFLAGS_DEBUG += -O2

darwin {
    DEFINES += ENABLE_JSC_MULTIPLE_THREADS=0
    contains(QT_CONFIG, coreservices) {
        LIBS_PRIVATE += -framework CoreServices
    } else {
        LIBS_PRIVATE += -framework CoreFoundation
    }
}
win32 {
    LIBS += -lwinmm
}

# Suppress 'LEAK' messages (see QTBUG-18201)
DEFINES += LOG_DISABLED=1

JAVASCRIPTCORE_JIT = no

# This line copied from WebCore.pro
DEFINES += WTF_USE_JAVASCRIPTCORE_BINDINGS=1 WTF_CHANGES=1

CONFIG(release, debug|release): DEFINES += NDEBUG

# Avoid JSC C API functions being exported.
DEFINES += JS_NO_EXPORT

INCLUDEPATH += \
    $$PWD/include \
    $$OUT_PWD/include \
    $$OUT_PWD/include/QtScript/$$[QT_VERSION]/QtScript \
    $$PWD/../../shared/qtscript/src/script \
    $$PWD/../../shared/qtscript/src/script/api

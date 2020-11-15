!win32: error("process_ctrlc_stub is Windows only")
message("process_ctrlc .1..................................")
CONFIG    -= qt
CONFIG    += console warn_on

include(../../../qtcreator.pri)
message("process_ctrlc .2..................................")
TEMPLATE  = app
TARGET    = qtcreator_ctrlc_stub
DESTDIR   = $$IDE_LIBEXEC_PATH

SOURCES   += process_ctrlc_stub.cpp
LIBS      += -luser32 -lshell32

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}
message("process_ctrlc .3..................................")
target.path  = $$INSTALL_LIBEXEC_PATH
INSTALLS    += target
message("process_ctrlc .4..................................")
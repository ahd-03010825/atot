TEMPLATE = lib
TARGET = atotlib
DEPENDPATH += .
CONFIG += dll

DEFINES += BUILD_ATOT

QT =

win32 {
  INCLUDEPATH += "E:/work/54_c_interface/lib/install/poco/debug/include"

  CONFIG(debug, debug|release) {
    LIBS += -L"E:/work/54_c_interface/lib/install/poco/debug/lib"
    LIBS += -lPocoFoundationd
    LIBS += -lPocoJSONd
    LIBS += -lPocoNetd
  } else {
    LIBS += -L"E:/work/54_c_interface/lib/install/poco/release/lib"
    LIBS += -lPocoFoundation
    LIBS += -lPocoJSON
    LIBS += -lPocoNet
  }
}

# Input
HEADERS += atot.h
SOURCES += atot.cpp

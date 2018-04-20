TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++1z

QMAKE_CXXFLAGS += -std=c++1z

SOURCES += main.cpp \
    memstatgrabber.cpp \
    memstatisticdata.cpp \
    statgrabber.cpp \
    statisticdata.cpp \
    diskstatgrabber.cpp \
    stringutilities.cpp \
    diskstatisticdata.cpp

HEADERS += \
    memstatgrabber.h \
    memstatisticdata.h \
    statgrabber.h \
    statisticdata.h \
    diskstatgrabber.h \
    stringutilities.h \
    diskstatisticdata.h

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    memstatgrabber.cpp \
    memstatisticdata.cpp \
    statgrabber.cpp \
    statisticdata.cpp \
    diskstatgrabber.cpp \
    stringutilities.cpp

HEADERS += \
    memstatgrabber.h \
    memstatisticdata.h \
    statgrabber.h \
    statisticdata.h \
    diskstatgrabber.h \
    stringutilities.h

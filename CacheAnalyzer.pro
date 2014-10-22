TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Plotter.cpp \
    Analyzer.cpp

HEADERS += \
    Plotter.h \
    Analyzer.h \
    PlotData.h

QMAKE_CXXFLAGS += -std=c++11

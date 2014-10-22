TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Plotter.cpp

HEADERS += \
    Plotter.h \
    Analyzer.h \
    PlotData.h \
    Measure.h

QMAKE_CXXFLAGS += -std=c++14

win32 {
    INCLUDEPATH += C:/Projects/Qt/boost_1_56_0
}

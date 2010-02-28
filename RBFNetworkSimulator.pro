# -------------------------------------------------
# Project created by QtCreator 2010-02-27T07:40:36
# -------------------------------------------------
TARGET = RBFNetworkSimulator
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    radialbasisfunction.cpp \
    gaussianbasisfunction.cpp \
    state.cpp \
    plot.cpp \
    kmeans.cpp \
    rbfnetwork.cpp
HEADERS += mainwindow.h \
    radialbasisfunction.h \
    gaussianbasisfunction.h \
    state.h \
    plot.h \
    kmeans.h \
    rbfnetwork.h
FORMS += mainwindow.ui
RESOURCES += resources.qrc
INCLUDEPATH += qwt/src
LIBS += -Lqwt/lib \
    -lqwtd6

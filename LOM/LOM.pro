#-------------------------------------------------
#
# Project created by QtCreator 2017-01-27T15:20:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport network

TARGET = LOM
TEMPLATE = app


# ROOT CERN linking.

QMAKE_CXXFLAGS += -m64 -pthread
QMAKE_LFLAGS += -m64 -pthread

INCLUDEPATH += /home/darya/root/include/

CONFIG += c++11

LIBS += -L"/home/darya/root/lib/"
LIBS += -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint
LIBS += -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc
LIBS += -pthread -lm -ldl -rdynamic


# Project files.

SOURCES += main.cpp\
    src/LOMInitParameters.cpp \
    src/LOMDataProcessor.cpp \
    src/LOMDataUpdater.cpp \
    qcustomplot/qcustomplot.cpp \
    src/QEndcapWidget.cpp \
    src/QColorBar.cpp \
    src/Logger.cpp \
    src/TCPTransporter.cpp \
    src/QNetworkSettings.cpp \
    src/LOMAmplitudes.cpp \
    src/LOMCounters.cpp \
    src/LOMHistograms.cpp \
    src/QHistPlot.cpp \
    src/QHistPoolWidget.cpp \
    src/QMenuConfig.cpp \
    src/LOMMainWindow.cpp \
    src/LuminosityCalculator.cpp

HEADERS  += \
    inc/LOMInitParameters.h \
    inc/LOMDataProcessor.h \
    inc/LOMDataUpdater.h \
    inc/AbstractTransporter.h \
    qcustomplot/qcustomplot.h \
    inc/QColorBar.h \
    inc/QEndcapWidget.h \
    inc/Constants.h \
    inc/Logger.h \
    inc/LogListener.h \
    inc/TCPTransporter.h \
    inc/QNetworkSettings.h \
    inc/LOMAmplitudes.h \
    inc/LOMCounters.h \
    inc/LOMHistograms.h \
    inc/QHistPlot.h \
    inc/QHistPoolWidget.h \
    inc/QMenuConfig.h \
    inc/LOMMainWindow.h \
    inc/LuminosityCalculator.h

FORMS    += \
    forms/QNetworkSettings.ui \
    forms/QHistPlot.ui \
    forms/QHistPoolWidget.ui \
    forms/QMenuConfig.ui \
    forms/LOMMainWindow.ui

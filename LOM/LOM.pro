#-------------------------------------------------
#
# Project created by QtCreator 2017-01-27T15:20:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    src/LOMView.cpp \
    src/LOMInitParameters.cpp \
    src/LOMEventData.cpp \
    src/LOMDataProcessor.cpp \
    src/LOMDataUpdater.cpp \
    src/AbstractTransporter.cpp \
    src/EndcapWidget.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS  += inc/LOMView.h \
    inc/LOMInitParameters.h \
    inc/LOMEventData.h \
    inc/LOMDataProcessor.h \
    inc/LOMDataUpdater.h \
    inc/AbstractTransporter.h \
    inc/EndcapWidget.h \
    qcustomplot/qcustomplot.h

FORMS    += forms/LOMView.ui

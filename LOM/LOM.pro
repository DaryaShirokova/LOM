#-------------------------------------------------
#
# Project created by QtCreator 2017-01-27T15:20:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LOM
TEMPLATE = app


SOURCES += main.cpp\
    src/LOMView.cpp \
    src/LOMInitParameters.cpp \
    src/LOMEventData.cpp \
    src/LOMDataProcessor.cpp \
    src/LOMDataUpdater.cpp \
    src/AbstractTransporter.cpp \
    src/EndcapWidget.cpp

HEADERS  += inc/LOMView.h \
    inc/LOMInitParameters.h \
    inc/LOMEventData.h \
    inc/LOMDataProcessor.h \
    inc/LOMDataUpdater.h \
    inc/AbstractTransporter.h \
    inc/EndcapWidget.h

FORMS    += forms/LOMView.ui

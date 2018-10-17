#-------------------------------------------------
#
# Project created by QtCreator 2018-10-12T22:41:38
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Drawing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    pixelartcanvas.cpp \
    palette.cpp \
    imagesequence.cpp \
    pixelimage.cpp \
    moviescreen.cpp

HEADERS += \
        mainwindow.h \
    pixelartcanvas.h \
    palette.h \
    common.h \
    imagesequence.h \
    pixelimage.h \
    moviescreen.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Pixeled.ttf \
    json_example \
    eraser_32x32.png \
    eraser_white_32x32.png \
    pen_white_32x32.png \
    pen_32x32.png \
    fill_32x32.png \
    fill_white_32x32.png

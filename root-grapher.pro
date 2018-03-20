#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T19:14:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = root-grapher
TEMPLATE = app


# ROOT INCLUDES
unix:LIBS += -L/home/taras/Documents/Soft/root/lib -lCore -lCint -lRIO -lNet \
        -lHist -lGraf -lGraf3d -lGpad -lTree \
        -lRint -lPostscript -lMatrix -lPhysics \
        -lGui -lMathCore -lThread
unix:INCLUDEPATH += /home/taras/Documents/Soft/root/include\


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cxx \
    qrootfile.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    qrootfile.h

FORMS    += mainwindow.ui

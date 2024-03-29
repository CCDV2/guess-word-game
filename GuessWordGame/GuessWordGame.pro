#-------------------------------------------------
#
# Project created by QtCreator 2019-02-28T19:23:34
#
#-------------------------------------------------

QT       += core gui sql network xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuessWordGame
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
    databaseserver.cpp \
    logindialog.cpp \
    gamewidget.cpp \
    registerdialog.cpp \
    simplifieduserinfowidget.cpp \
    loginorregisterdialog.cpp \
    detaileduserinfodialog.cpp \
    ranklistwidget.cpp \
    word.cpp \
    questionwidget.cpp \
    gamemodeselectwidget.cpp \
    endgamedialog.cpp \
    gamecache.cpp \
    tcpclient.cpp \
    user.cpp \
    onlineuserwidget.cpp \
    battlechoosedialog.cpp

HEADERS += \
        mainwindow.h \
    datastructure.h \
    databaseserver.h \
    logindialog.h \
    gamewidget.h \
    registerdialog.h \
    simplifieduserinfowidget.h \
    loginorregisterdialog.h \
    detaileduserinfodialog.h \
    ranklistwidget.h \
    word.h \
    questionwidget.h \
    gamemodeselectwidget.h \
    endgamedialog.h \
    gamecache.h \
    tcpclient.h \
    user.h \
    onlineuserwidget.h \
    battlechoosedialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
	/qss/mystyle.qss

DISTFILES +=




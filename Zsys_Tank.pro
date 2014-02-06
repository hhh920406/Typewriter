#-------------------------------------------------
#
# Project created by QtCreator 2011-06-29T22:44:45
#
#-------------------------------------------------

QT       += core gui

TARGET = Zsys_Tank
TEMPLATE = app


SOURCES += main.cpp \
    tankform.cpp \
    loading.cpp \
    mainmenu.cpp \
    gamebutton.cpp \
    help.cpp \
    achieve.cpp \
    number.cpp \
    integer.cpp \
    fraction.cpp \
    gameobject.cpp \
    moveobject.cpp \
    game.cpp \
    healthshow.cpp \
    tank.cpp \
    environment.cpp \
    over.cpp \
    stage.cpp \
    pause.cpp \
    gamekeyedit.cpp \
    config.cpp \
    choice.cpp \
    aboutus.cpp \
    textarea.cpp \
    gamewidget.cpp \
    snake.cpp \
    snakescene.cpp \
    cellintro.cpp \
    cellular.cpp \
    cellscene.cpp

HEADERS  += \
    tankform.h \
    loading.h \
    defination.h \
    mainmenu.h \
    gamebutton.h \
    help.h \
    achieve.h \
    number.h \
    integer.h \
    fraction.h \
    gameobject.h \
    moveobject.h \
    game.h \
    healthshow.h \
    tank.h \
    environment.h \
    over.h \
    stage.h \
    pause.h \
    gamekeyedit.h \
    config.h \
    choice.h \
    aboutus.h \
    textarea.h \
    gamewidget.h \
    snake.h \
    snakescene.h \
    cellintro.h \
    cellular.h \
    cellscene.h

FORMS += \
    tankform.ui

RESOURCES += \
    resource.qrc

RC_FILE = icon.rc

TRANSLATIONS += Lang_CH.ts

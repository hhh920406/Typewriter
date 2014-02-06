#-------------------------------------------------
#
# Project created by QtCreator 2013-09-26T19:46:04
#
#-------------------------------------------------

QT       += core gui network testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = monitor
TEMPLATE = app

INCLUDEPATH += ./include
INCLUDEPATH += ./test

TRANSLATIONS += lang/Lang_CH.ts

SOURCES += src/main.cpp\
    src/MainWindow.cpp \
    src/ClientInfo.cpp \
    src/IPAddress.cpp \
    test/test_IPAddress.cpp \
    test/test_ClientInfo.cpp \
    src/ClientManager.cpp \
    test/test_ClientManager.cpp \
    src/TcpServer.cpp \
    src/ColorWidget.cpp \
    src/UdpServer.cpp \
    src/LineChartWidget.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS  += include/MainWindow.h \
    include/ClientInfo.h \
    include/IPAddress.h \
    test/test_IPAddress.h \
    test/test_ClientInfo.h \
    include/ClientManager.h \
    test/test_ClientManager.h \
    include/TcpServer.h \
    include/ColorWidget.h \
    include/UdpServer.h \
    include/LineChartWidget.h

FORMS    += form/MainWindow.ui

RESOURCES += \
    resource/resource.qrc

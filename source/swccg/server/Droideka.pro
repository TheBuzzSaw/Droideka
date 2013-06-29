#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T22:41:12
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Droideka
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    GameServer.cpp \
    ClientConnection.cpp

HEADERS += \
    GameServer.hpp \
    ClientConnection.hpp

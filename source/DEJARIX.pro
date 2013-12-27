#-------------------------------------------------
#
# Project created by QtCreator 2013-06-19T18:03:56
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DEJARIX
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    MainWidget.cpp \
    CardSpecifications.cpp \
    CardBuilder.cpp \
    CardBuffer.cpp \
    CardActor.cpp \
    Camera.cpp \
    Animation.cpp \
    TableBuffer.cpp \
    AnimationCollection.cpp \
    swccg/Card.cpp \
    CardDrawTool.cpp \
    MenuRing.cpp \
    swccg/LocationPopper.cpp \
    MenuRingItem.cpp \
    BasicBuilder.cpp \
    BasicProgram.cpp \
    BasicBufferObject.cpp

HEADERS  += MainWindow.hpp \
    MainWidget.hpp \
    CardSpecifications.hpp \
    CardBuilder.hpp \
    CardBuffer.hpp \
    CardActor.hpp \
    Rotation.hpp \
    Camera.hpp \
    Animation.hpp \
    TableBuffer.hpp \
    AnimationCollection.hpp \
    swccg/Card.hpp \
    CardDrawTool.hpp \
    MenuRing.hpp \
    swccg/LocationPopper.hpp \
    MenuRingItem.hpp \
    BasicBuilder.hpp \
    BasicProgram.hpp \
    BasicBufferObject.hpp

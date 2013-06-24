#-------------------------------------------------
#
# Project created by QtCreator 2013-06-19T18:03:56
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DEJARIX
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MainWidget.cpp \
    CardSpecifications.cpp \
    CardBuilder.cpp \
    CardBuffer.cpp \
    MainProgram.cpp \
    CardActor.cpp \
    Rotation.cpp \
    Camera.cpp \
    Animation.cpp \
    TableBuffer.cpp \
    AnimationCollection.cpp \
    swccg/CardPile.cpp \
    swccg/Card.cpp

HEADERS  += MainWindow.hpp \
    MainWidget.hpp \
    CardSpecifications.hpp \
    CardBuilder.hpp \
    CardBuffer.hpp \
    MainProgram.hpp \
    CardActor.hpp \
    Rotation.hpp \
    Camera.hpp \
    Animation.hpp \
    TableBuffer.hpp \
    AnimationCollection.hpp \
    swccg/CardPile.hpp \
    swccg/Card.hpp

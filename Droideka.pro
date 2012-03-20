#-------------------------------------------------
#
# Project created by QtCreator 2012-02-05T16:47:31
#
#-------------------------------------------------

QT       += core gui opengl network

TARGET = Droideka
TEMPLATE = app


SOURCES += main.cpp\
        LoginWindow.cpp \
    SceneGraphNode.cpp \
    CardNode.cpp \
    CardModel.cpp \
    TrackballCamera.cpp \
    VertexBufferObject.cpp \
    IndexBufferObject.cpp \
    MainWindow.cpp \
    CanvasOpenGL.cpp

HEADERS  += LoginWindow.h \
    Matrix4x4.hpp \
    SceneGraphNode.hpp \
    Vectors.hpp \
    CardNode.hpp \
    CardModel.hpp \
    TrackballCamera.hpp \
    VertexBufferObject.hpp \
    IndexBufferObject.hpp \
    MainWindow.hpp \
    CanvasOpenGL.hpp

FORMS    += LoginWindow.ui

RESOURCES +=

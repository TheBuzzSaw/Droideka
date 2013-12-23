#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include "Camera.hpp"
#include "CardDrawTool.hpp"
#include "TableBuffer.hpp"
#include "MainProgram.hpp"
#include "AnimationCollection.hpp"
#include "swccg/LocationPopper.hpp"
#include <QWidget>
#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QImage>
#include <QVector>
#include <QPoint>

namespace MouseMode
{
    enum Mode { None, InsertLocation };
}

class MainWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = 0);
    virtual ~MainWidget();

    void dump();

protected slots:
    void onTimer();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);

private:
    GLuint loadImage(const QImage& image);
    GLuint loadText(const QString& text);
    QVector3D unproject(QPoint pixel);

    MainProgram* _program;
    CardBuffer* _cardBuffer;
    CardDrawTool* _drawTool;
    TableBuffer* _tableBuffer;

    AnimationCollection _animations;
    GLint _viewport[4];
    QMatrix4x4 _projectionMatrix;
    GLuint _tableTexture;
    Camera _camera;
    bool _isCameraMoving;
    QPoint _mouse;

    GLuint _textures[2];
    QVector<CardActor> _locationActors;
    float _locationSpan;
    MouseMode::Mode _mouseMode;
    LocationPopper _locationPopper;
    int _locationTarget;
};

#endif

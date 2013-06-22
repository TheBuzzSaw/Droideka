#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include "Camera.hpp"
#include "CardActor.hpp"
#include "CardBuffer.hpp"
#include "MainProgram.hpp"
#include <QWidget>
#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QImage>

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

private:
    GLuint loadImage(const QImage& image);

    MainProgram* _program;
    CardBuffer* _cardBuffer;
    CardActor _cardActor;
    QMatrix4x4 _projectionMatrix;
    GLuint _frontTexture;
    GLuint _backTexture;
    Camera _camera;
    bool _isCameraMoving;
    int _mouseX;
    int _mouseY;
};

#endif

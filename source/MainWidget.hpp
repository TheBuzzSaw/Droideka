#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

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

protected slots:
    void onTimer();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mousePressEvent(QMouseEvent* event);

private:
    GLuint loadImage(const QImage& image);

    MainProgram* _program;
    CardBuffer* _cardBuffer;
    QMatrix4x4 _projection;
    GLuint _frontTexture;
    GLuint _backTexture;
    float _rotation;
};

#endif

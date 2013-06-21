#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include "CardBuffer.hpp"
#include <QWidget>
#include <QMatrix4x4>

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

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
    CardBuffer* _cardBuffer;
    QMatrix4x4 _projection;
    float _rotation;

    QOpenGLShaderProgram* _program;
    GLuint _frontTexture;
    GLuint _backTexture;
    GLuint _positionAttribute;
    GLuint _textureAttribute;
    GLuint _matrixUniform;
    GLuint _textureUniform;
};

#endif

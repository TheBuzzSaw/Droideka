#ifndef WIDGETTESTOPENGL_HPP
#define WIDGETTESTOPENGL_HPP

#include "Matrix4x4.hpp"
#include <QGLWidget>
#include <QGLBuffer>

class WidgetTestOpenGL : public QGLWidget
{
    Q_OBJECT

public:
    WidgetTestOpenGL(QWidget* inParent = 0);
    ~WidgetTestOpenGL();

public slots:
    void onPulse();

protected:
    virtual void resizeGL(int inWidth, int inHeight);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent* inEvent);
    virtual void mouseMoveEvent(QMouseEvent* inEvent);
    virtual void keyPressEvent(QKeyEvent* inEvent);

private:
    void testFolders();

    CGE::Matrix4x4<float> mProjectionMatrix;
    CGE::Matrix4x4<float> mModelViewMatrix;
    float mRotation;
    QGLBuffer mBuffer;
};

#endif

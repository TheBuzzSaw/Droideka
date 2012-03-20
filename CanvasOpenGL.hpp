#ifndef WIDGETTESTOPENGL_HPP
#define WIDGETTESTOPENGL_HPP

#include "Matrix4x4.hpp"
#include "CardModel.hpp"
#include <QGLWidget>

class CanvasOpenGL : public QGLWidget
{
    Q_OBJECT

public:
    CanvasOpenGL(QWidget* inParent = 0);
    ~CanvasOpenGL();

public slots:
    void onPulse();

protected:
    virtual void resizeGL(int inWidth, int inHeight);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent* inEvent);
    virtual void mouseMoveEvent(QMouseEvent* inEvent);

private:
    void testFolders();

    mat4f mProjectionMatrix;
    mat4f mModelViewMatrix;
    float mRotation;
    CardModel* mCardModel;
    GLuint mFrontTexture;
    GLuint mBackTexture;
};

#endif

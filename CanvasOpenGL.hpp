#ifndef CANVASOPENGL_HPP
#define CANVASOPENGL_HPP

#include "Matrix4x4.hpp"
#include "CardActor.hpp"
#include <QGLWidget>

class CanvasOpenGL : public QGLWidget
{
    Q_OBJECT

public:
    CanvasOpenGL(QWidget* inParent = 0);
    ~CanvasOpenGL();

protected slots:
    void onPulse();

protected:
    virtual void resizeGL(int inWidth, int inHeight);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent* inEvent);
    virtual void mouseMoveEvent(QMouseEvent* inEvent);

private:
    void testFolders();
    GLuint loadCardTexture(const QImage& inImage);

    mat4f mProjectionMatrix;
    mat4f mModelViewMatrix;
    float mRotation;
    CardModel* mCardModel;
    CardActor* mCardNode;
    GLuint mFrontTexture;
    GLuint mBackTexture;
};

#endif

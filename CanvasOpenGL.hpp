#ifndef CANVASOPENGL_HPP
#define CANVASOPENGL_HPP

#include "TrackballCamera.hpp"
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
    TrackballCamera mCamera;
    Actor mHeadActor;
    CardModel* mCardModel;
    CardActor* mCardActor;
    GLuint mFrontTexture;
    GLuint mBackTexture;
};

#endif

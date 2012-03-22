#ifndef CANVASOPENGL_HPP
#define CANVASOPENGL_HPP

#include "TrackballCamera.hpp"
#include "CardActor.hpp"
#include <QGLWidget>
#include <QList>
#include <QVector>
#include <QMap>

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
    virtual void mouseReleaseEvent(QMouseEvent* inEvent);
    virtual void mouseMoveEvent(QMouseEvent* inEvent);
    virtual void wheelEvent(QWheelEvent* inEvent);

private:
    enum { None, RotateCamera, PanCamera } mMouseMode;

    int mAnchorX;
    int mAnchorY;

    void destroyAll();
    void testFolders();
    GLuint loadCardTextureByName(const QString& inName);

    QList<CardActor*> mCardActors;
    QVector<GLuint> mTextures;
    QMap<QString, GLuint> mTexturesByName;

    mat4f mProjectionMatrix;
    TrackballCamera mCamera;
    Actor mHeadActor;
    CardModel* mCardModel;
};

#endif

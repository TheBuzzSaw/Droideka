#ifndef CANVASOPENGL_HPP
#define CANVASOPENGL_HPP

#include "TrackballCamera.hpp"
#include "CardActor.hpp"
#include "TableActor.hpp"
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
    void unproject(GLint inX, GLint inY, GLfloat inDepth,
        const mat4f& inModelViewProjectionMatrix,
        GLfloat* inResult);

    enum { None, RotateCamera, PanCamera } mMouseMode;

    int mAnchorX;
    int mAnchorY;

    int mSampleX;
    int mSampleY;
    float mMouse3D[4];

    void destroyAll();
    void testFolders();
    GLuint loadCardTextureByName(const QString& inName);

    CardActor* mSelectedCard;
    QList<CardActor*> mCardActors;
    QVector<GLuint> mTextures;
    QMap<QString, GLuint> mTexturesByName;

    mat4f mProjectionMatrix;
    GLint mViewport[4];
    TrackballCamera mCamera;
    Actor mHeadActor;
    CardModel* mCardModel;
    TableModel* mTableModel;
    TableActor* mTableActor;
    GLuint mTableTexture;
};

#endif

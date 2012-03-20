#include "CanvasOpenGL.hpp"
#include <QtOpenGL>

CanvasOpenGL::CanvasOpenGL(QWidget *inParent)
    : QGLWidget(QGLFormat(QGL::AlphaChannel
                          | QGL::Rgba
                          | QGL::DepthBuffer
                          | QGL::DoubleBuffer
                          | QGL::DeprecatedFunctions
                          ), inParent)
{
    mRotation = 0.0f;
    setMouseTracking(true);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onPulse()));
    timer->start(25);
    mCardModel = 0;
}

CanvasOpenGL::~CanvasOpenGL()
{
    deleteTexture(mFrontTexture);
    deleteTexture(mBackTexture);
    delete mCardModel;
}

void CanvasOpenGL::onPulse()
{
    mRotation += 1.0f;

    if (mRotation > 180.0f) mRotation -= 360.0f;

    mModelViewMatrix.loadIdentity();
    //mModelViewMatrix.rotateZ(mRotation);
    mModelViewMatrix.translate(0.0f, 0.0f, -20.0f);
    mModelViewMatrix.rotateY(mRotation);
    updateGL();
}

void CanvasOpenGL::initializeGL()
{
    mCardModel = new CardModel;
    mFrontTexture = bindTexture(QImage("localuprising.gif"), GL_TEXTURE_2D);
    mBackTexture = bindTexture(QImage("liberation.gif"), GL_TEXTURE_2D);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glClearColor(0.1f, 0.1f, 0.6f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
    glColor3f(0.0f, 0.0f, 0.0f);
}

void CanvasOpenGL::resizeGL(int inWidth, int inHeight)
{
    glViewport(0, 0, inWidth, inHeight);

    float ratio = float(inWidth) / float(inHeight);

    mProjectionMatrix.loadIdentity();
    mProjectionMatrix.perspective(30.0f, ratio, 1.0f, 1000.0f, true);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(mProjectionMatrix);
    glMatrixMode(GL_MODELVIEW);
}

void CanvasOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadMatrixf(mModelViewMatrix);

    mCardModel->drawFront(mFrontTexture);
    mCardModel->drawEdge();
    mCardModel->drawBack(mBackTexture);
}

void CanvasOpenGL::mousePressEvent(QMouseEvent* inEvent)
{
    qDebug() << inEvent->pos();
}

void CanvasOpenGL::mouseMoveEvent(QMouseEvent* inEvent)
{
    (void)inEvent;
}

void CanvasOpenGL::testFolders()
{
    QDir home = QDir::home();
    bool success = home.mkpath("Droideka/data/huh");
    qDebug() << (success ? "WOOT" : "dawww");
}

GLuint CanvasOpenGL::loadCardTexture(const QImage& inImage)
{
    GLuint outTexture = 0;

    if (!inImage.isNull())
    {
        QImage adjustedImage = inImage.scaled(QSize(512, 512), Qt::KeepAspectRatio,
            Qt::FastTransformation);
    }

    return outTexture;
}

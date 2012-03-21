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
    mCardNode = 0;
}

CanvasOpenGL::~CanvasOpenGL()
{
    deleteTexture(mFrontTexture);
    deleteTexture(mBackTexture);
    delete mCardNode;
    delete mCardModel;
}

void CanvasOpenGL::onPulse()
{
    mRotation += 1.0f;

    if (mRotation > 180.0f) mRotation -= 360.0f;

    mModelViewMatrix.loadIdentity();
    mModelViewMatrix.translate(0.0f, 0.0f, -20.0f);
    mModelViewMatrix.rotateY(mRotation);

    mCardNode->updateMatrices(mat4f(), mModelViewMatrix);
    updateGL();
}

void CanvasOpenGL::initializeGL()
{
    mCardModel = new CardModel;
    mFrontTexture = loadCardTexture(QImage("localuprising.gif"));
    mBackTexture = loadCardTexture(QImage("liberation.gif"));
    mCardNode = new CardActor(*mCardModel, mFrontTexture, mBackTexture);

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

    mCardNode->draw();
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
        QImage square(QSize(512, 512), inImage.format());
        QPainter painter(&square);
        painter.drawImage(QRect(0, 0, 512, 512), inImage);
        qDebug() << "square" << square.size();
        outTexture = bindTexture(square, GL_TEXTURE_2D);
    }

    return outTexture;
}

#include "WidgetTestOpenGL.hpp"
#include <QtOpenGL>

WidgetTestOpenGL::WidgetTestOpenGL(QWidget *inParent)
    : QGLWidget(QGLFormat(QGL::AlphaChannel | QGL::DepthBuffer | QGL::DoubleBuffer | QGL::DeprecatedFunctions), inParent)
{
    mRotation = 0.0f;
    setMouseTracking(true);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onPulse()));
    timer->start(25);

    setWindowTitle(tr("Droideka"));
    resize(QSize(400, 400));
}

WidgetTestOpenGL::~WidgetTestOpenGL()
{
}

void WidgetTestOpenGL::onPulse()
{
    mRotation += 1.0f;

    if (mRotation > 180.0f) mRotation -= 360.0f;

    mModelViewMatrix.loadIdentity();
    mModelViewMatrix.rotateZ(mRotation);
    updateGL();
}

void WidgetTestOpenGL::resizeGL(int inWidth, int inHeight)
{
    glViewport(0, 0, inWidth, inHeight);

    float ratio = float(inWidth) / float(inHeight);

    mProjectionMatrix.loadIdentity();
    mProjectionMatrix.perspective(30.0f, ratio, 1.0f, 1000.0f, true);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(mProjectionMatrix);
    glMatrixMode(GL_MODELVIEW);
}

void WidgetTestOpenGL::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glClearColor(0.1f, 0.1f, 0.6f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void WidgetTestOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadMatrixf(mModelViewMatrix);
    //glLoadIdentity();

    const float z = -10.0f;
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, z);
    glVertex3f(0.0f, 1.0f, z);
    glVertex3f(1.0f, 0.0f, z);
    glEnd();
}

void WidgetTestOpenGL::mousePressEvent(QMouseEvent* inEvent)
{
}

void WidgetTestOpenGL::mouseMoveEvent(QMouseEvent* inEvent)
{
}

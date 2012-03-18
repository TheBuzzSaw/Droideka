#include "WidgetTestOpenGL.hpp"
#include <QtOpenGL>

WidgetTestOpenGL::WidgetTestOpenGL(QWidget *inParent)
    : QGLWidget(QGLFormat(QGL::AlphaChannel
                          | QGL::Rgba
                          | QGL::DepthBuffer
                          | QGL::DoubleBuffer
                          | QGL::DeprecatedFunctions
                          ), inParent)
{
    mRotation = 0.0f;
    setMouseTracking(true);

    setWindowTitle(QString("Droideka"));
    resize(QSize(400, 400));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onPulse()));
    timer->start(25);
}

WidgetTestOpenGL::~WidgetTestOpenGL()
{
    mBuffer.destroy();
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
    const GLfloat z = -10.0f;
    GLfloat vertices[] = {
        1.0f, 1.0f, z,
        1.0f, -1.0f, z,
        -1.0f, -1.0f, z,
        -1.0f, 1.0f, z
        };

    mBuffer.create();
    mBuffer.bind();
    mBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mBuffer.allocate(vertices, sizeof(vertices));

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
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void WidgetTestOpenGL::mousePressEvent(QMouseEvent* inEvent)
{
    (void)inEvent;
}

void WidgetTestOpenGL::mouseMoveEvent(QMouseEvent* inEvent)
{
    (void)inEvent;
}

#include "MainWidget.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QVector2D>

MainWidget::MainWidget(QWidget* parent) : QGLWidget(parent)
{
    _program = 0;
    _cardBuffer = 0;
    _drawTool = 0;
    _tableBuffer = 0;
    _isCameraMoving = false;
    _camera.distance(32.0f);
    _camera.angle(Rotation::fromDegrees(-10.0f));
}

MainWidget::~MainWidget()
{
    _program->release();

    deleteTexture(_tableTexture);
    delete _drawTool;
    delete _tableBuffer;
    delete _cardBuffer;
    delete _program;
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(16);

    _program = new MainProgram;

    _tableTexture = loadImage(QImage("../wood.jpg"));

    _textures[0] = loadImage(QImage("../localuprising.gif"));
    _textures[1] = loadImage(QImage("../liberation.gif"));

    CardSpecifications specifications;
    CardBuilder builder(specifications);
    _cardBuffer = new CardBuffer(builder);
    _drawTool = new CardDrawTool(*_program, *_cardBuffer, _projectionMatrix);
    _tableBuffer = new TableBuffer;

    for (int i = 0; i < 3; ++i)
    {
        CardActor actor;
        actor.topTexture(_textures[0]);
        actor.bottomTexture(_textures[1]);
        actor.position(QVector3D(float(i)
            * _cardBuffer->specifications().height(), 0.0f,
            _cardBuffer->specifications().depth() / 2.0f));

        actor.rotation(Rotation::fromDegrees(90.0f));

        _actors.append(actor);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

    _program->bind();
}

void MainWidget::resizeGL(int w, int h)
{
    float ratio = float(w) / float(h);
    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(60.0f, ratio, 1.0f, 1000.0f);
    glViewport(0, 0, w, h);
    glGetIntegerv(GL_VIEWPORT, _viewport);
}

void MainWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _drawTool->bind();

    for (int i = 0; i < _actors.size(); ++i)
    {
        _drawTool->draw(_actors[i]);
    }

    _program->enableTexture(true);
    _program->setMatrix(_projectionMatrix * _camera.matrix());
    _program->setHighlight(QVector4D());
    glBindTexture(GL_TEXTURE_2D, _tableTexture);
    _tableBuffer->bind(_program->positionAttribute(),
        _program->textureAttribute());
    _tableBuffer->draw();
}

void MainWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        _isCameraMoving = true;
        _mouseX = event->x();
        _mouseY = event->y();
    }
    else if (event->button() == Qt::LeftButton)
    {
        QVector3D result = unproject(event->x(), event->y());
        qDebug() << result;
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
        _isCameraMoving = false;
}

void MainWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (_isCameraMoving)
    {
        int deltaX = event->x() - _mouseX;
        int deltaY = event->y() - _mouseY;

        _camera.adjustRotation(Rotation::fromDegrees(float(deltaX) / 3.0f));
        _camera.adjustAngle(Rotation::fromDegrees(float(deltaY) / 3.0f));

        _mouseX = event->x();
        _mouseY = event->y();
    }
}

void MainWidget::wheelEvent(QWheelEvent* event)
{
    const float delta = 3.0f;
    _camera.adjustDistance(event->delta() > 0 ? -delta : delta);
}

void MainWidget::onTimer()
{
    _animations.updateAll();
    _camera.update();

    for (int i = 0; i < _actors.size(); ++i)
    {
        _actors[i].update(_camera.matrix());
    }

    updateGL();
}

GLuint MainWidget::loadImage(const QImage& image)
{
    GLuint result = 0;

    if (image.width() > 0 && image.height() > 0)
    {
        int width = 1;
        int height = 1;

        while (width < image.width()) width *= 2;
        while (height < image.height()) height *= 2;

        if (width > image.width() || height > image.height())
        {
            result = bindTexture(image.scaled(width, height));
        }
        else
        {
            result = bindTexture(image);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    return result;
}

QVector3D MainWidget::unproject(int x, int y)
{
    y = height() - y;

    GLfloat depthSample;
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depthSample);

    QVector4D v;
    v.setX(float(x - _viewport[0]) * 2.0f / float(_viewport[2]) - 1.0f);
    v.setY(float(y - _viewport[1]) * 2.0f / float(_viewport[3]) - 1.0f);
    v.setZ(2.0f * depthSample - 1.0f);
    v.setW(1.0f);

    QMatrix4x4 modelViewProjectionMatrix = _projectionMatrix
        * _camera.matrix();
    QMatrix4x4 inverse = modelViewProjectionMatrix.inverted();
    return (inverse * v).toVector3DAffine();
}

void MainWidget::dump()
{
}

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
    _tableBuffer = 0;
    _isCameraMoving = false;
    _camera.distance(12.0f);
}

MainWidget::~MainWidget()
{
    _program->release();

    deleteTexture(_frontTexture);
    deleteTexture(_backTexture);
    delete _tableBuffer;
    delete _cardBuffer;
    delete _program;
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(25);

    _program = new MainProgram;

    _tableTexture = loadImage(QImage("../wood.jpg"));
    _frontTexture = loadImage(QImage("../localuprising.gif"));
    _backTexture = loadImage(QImage("../liberation.gif"));

    for (int i = 0; i < ActorCount; ++i)
    {
        _cardActors[i].topTexture(_frontTexture);
        _cardActors[i].bottomTexture(_backTexture);
        _cardActors[i].position(QVector3D(0.0f, i, i + 3));
        _cardActors[i].rotation(Rotation::fromDegrees(45.0f));
        _cardActors[i].flip(Rotation::fromDegrees(45.0f));
    }

    CardSpecifications specifications;
    //specifications.depth(1.0f);
    CardBuilder builder(specifications);
    _cardBuffer = new CardBuffer(builder);
    _tableBuffer = new TableBuffer;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

    _program->bind();
}

void MainWidget::resizeGL(int w, int h)
{
    float ratio = float(w) / float(h);
    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(60.0f, ratio, 1.0f, 100.0f);
    glViewport(0, 0, w, h);
}

void MainWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _cardBuffer->bind(_program->positionAttribute(),
        _program->textureAttribute());

    for (int i = 0; i < ActorCount; ++i)
    {
        _program->setMatrix(_projectionMatrix
           * _cardActors[i].modelViewMatrix());
        _program->enableTexture(false);
        _cardBuffer->drawMiddle();
        _program->enableTexture(true);

        if (_cardActors[i].isTopVisible())
        {
            glBindTexture(GL_TEXTURE_2D, _cardActors[i].topTexture());
            _cardBuffer->drawTop();
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, _cardActors[i].bottomTexture());
            _cardBuffer->drawBottom();
        }
    }

    _program->setMatrix(_projectionMatrix * _camera.matrix());
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
    _camera.update();

    for (int i = 0; i < ActorCount; ++i)
    {
        _cardActors[i].update(_camera.matrix());
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

        QImage square(width, height, image.format());
        QPainter painter(&square);
        painter.drawImage(QRect(0, 0, square.width(), square.height()), image);
        result = bindTexture(square);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    return result;
}

void MainWidget::dump()
{
}

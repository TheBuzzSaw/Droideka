#include "MainWidget.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QDir>
#include <QVector2D>

MainWidget::MainWidget(QWidget* parent) : QGLWidget(parent)
{
    _program = 0;
    _isCameraMoving = false;
    _camera.distance(12.0f);

#ifdef Q_OS_MAC
    qDebug() << QDir::currentPath();
    QDir::setCurrent("../../..");
    qDebug() << QDir::currentPath();
#endif
}

MainWidget::~MainWidget()
{
    deleteTexture(_frontTexture);
    deleteTexture(_backTexture);
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

    _frontTexture = loadImage(QImage("../localuprising.gif"));
    _backTexture = loadImage(QImage("../liberation.gif"));

    CardSpecifications specifications;
    //specifications.depth(1.0f);
    CardBuilder builder(specifications);
    _cardBuffer = new CardBuffer(builder);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
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
    _camera.update();
    _cardActor.update(_camera.matrix());

    _program->bind();
    _program->setMatrix(_projectionMatrix * _cardActor.modelViewMatrix());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _cardBuffer->bind(_program->positionAttribute(),
        _program->textureAttribute());
    _program->enableTexture(false);
    _cardBuffer->drawMiddle();
    _program->enableTexture(true);

    if (!_cardActor.isTopVisible())
    {
        glBindTexture(GL_TEXTURE_2D, _backTexture);
        _cardBuffer->drawBottom();
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, _frontTexture);
        _cardBuffer->drawTop();
    }

    _program->release();
}

void MainWidget::mousePressEvent(QMouseEvent* event)
{
    //qDebug() << event->x() << event->y();
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

void MainWidget::onTimer()
{
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

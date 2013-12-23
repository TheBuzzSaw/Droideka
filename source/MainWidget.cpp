#include "MainWidget.hpp"
#include "MenuRing.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QVector2D>

MainWidget::MainWidget(QWidget* parent)
    : QGLWidget(parent)
    , _program(nullptr)
    , _cardBuffer(nullptr)
    , _drawTool(nullptr)
    , _tableBuffer(nullptr)
    , _isCameraMoving(false)
    , _locationSpan(0.0f)
    , _mouseMode(MouseMode::None)
{
    _camera.distance(32.0f);
    _camera.angle(RotationF::fromDegrees(-10.0f));
    setMouseTracking(true);
}

MainWidget::~MainWidget()
{
    _program->release();

    deleteTexture(_textures[1]);
    deleteTexture(_textures[0]);
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
    //_tableTexture = loadText("DEJARIX");

    _textures[0] = loadImage(QImage("../localuprising.gif"));
    _textures[1] = loadImage(QImage("../liberation.gif"));

    CardSpecifications specifications;
    CardBuilder builder(specifications);
    _cardBuffer = new CardBuffer(builder);
    _drawTool = new CardDrawTool(*_program, *_cardBuffer, _projectionMatrix);
    _tableBuffer = new TableBuffer;

    _locationSpan = _cardBuffer->specifications().height()
        + 1.0f / 8.0f;

    for (int i = 0; i < 6; ++i)
    {
        CardActor actor;
        actor.topTexture(_textures[0]);
        actor.bottomTexture(_textures[1]);

        actor.rotation(RotationF::fromDegrees(90.0f));

        _locationActors.append(actor);
    }

    float count = float(_locationActors.size() - 1);
    float firstX = count * _locationSpan / -2.0f;

    for (int i = 0; i < _locationActors.size(); ++i)
    {
        _locationActors[i].position(QVector3D(firstX + float(i)
            * _locationSpan, 0.0f, specifications.depth() / 2.0f));
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.2f, 0.0f, 0.0f, 1.0f);

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

    for (int i = 0; i < _locationActors.size(); ++i)
    {
        _drawTool->draw(_locationActors[i]);
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
        _mouse = event->pos();
    }
    else if (event->button() == Qt::LeftButton)
    {
        //QVector3D result = unproject(event->x(), event->y());
        //qDebug() << result;

        QPoint center(width() / 2, height() / 2);
        QPoint direction = event->pos() - center;
        //qDebug() << "center: " << center;
        //qDebug() << "click: " << event->pos();
        qDebug() << "direction: " << direction;

        RotationF rotation;

        if (MenuRing::tryGetAngle(direction, 8, rotation))
        {
            qDebug() << "result: " << rotation.toDegrees();
        }
        else
        {
            qDebug() << "too close to origin";
        }
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
        _isCameraMoving = false;
}

void MainWidget::mouseMoveEvent(QMouseEvent* event)
{
    QVector3D mousePosition = unproject(event->pos());
    float radius = _locationSpan / 2.0f;

    if (_mouseMode == MouseMode::None)
    {
        if (mousePosition.y() > -radius && mousePosition.y() < radius)
        {
            _mouseMode = MouseMode::InsertLocation;
        }
    }

    if (_mouseMode == MouseMode::InsertLocation)
    {
        if (mousePosition.y() <= -radius || mousePosition.y() >= radius)
        {
            _locationTarget = 0xdeadbeef;
            _locationPopper.clear();
            _mouseMode = MouseMode::None;
        }
        else
        {
            float locationsSpan = float(_locationActors.size())
                * _locationSpan;
            float region = locationsSpan + mousePosition.x() * 2.0f;
            int halfRegionCount = int(region / _locationSpan) + 1;
            int locationTarget = halfRegionCount / 2 - 1;

            if (locationTarget >= -1 && locationTarget < _locationActors.size()
                && locationTarget != _locationTarget)
            {
                _locationTarget = locationTarget;

                CardActor* a = nullptr;
                CardActor* b = nullptr;

                if (_locationTarget > -1)
                    a = _locationActors.data() + _locationTarget;

                if (_locationTarget < _locationActors.size() - 1)
                    b = _locationActors.data() + _locationTarget + 1;

                _locationPopper.set(a, b);
            }
        }
    }

    if (_isCameraMoving)
    {
        QPoint delta = event->pos() - _mouse;

        _camera.adjustRotation(RotationF::fromDegrees(float(delta.x()) / 3.0f));
        _camera.adjustAngle(RotationF::fromDegrees(float(delta.y()) / 3.0f));

        _mouse = event->pos();
    }
}

void MainWidget::wheelEvent(QWheelEvent* event)
{
    const float Delta = 3.0f;
    _camera.adjustDistance(event->delta() > 0 ? -Delta : Delta);
}

void MainWidget::onTimer()
{
    _animations.updateAll();
    _camera.update();

    for (int i = 0; i < _locationActors.size(); ++i)
    {
        _locationActors[i].update(_camera.matrix());
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

GLuint MainWidget::loadText(const QString& text)
{
    GLuint result = 0;

    QFont font("../DejaVuSans.ttf");
    font.setPixelSize(64);
    QImage image(256, 256, QImage::Format_ARGB32);
    image.fill(QColor(0, 0, 0, 0));

    QPainter painter(&image);
    painter.setFont(font);
    painter.setPen(Qt::green);
    painter.drawText(image.rect(), Qt::AlignCenter, text);
    result = loadImage(image);

    return result;
}

QVector3D MainWidget::unproject(QPoint pixel)
{
    int x = pixel.x();
    int y = height() - pixel.y();

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

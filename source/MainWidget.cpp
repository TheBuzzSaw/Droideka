#include "MainWidget.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

MainWidget::MainWidget(QWidget* parent) : QGLWidget(parent)
{
    _program = 0;
    _rotation = 0.0;
}

MainWidget::~MainWidget()
{
    delete _cardBuffer;
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(25);

    const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    _program = new QOpenGLShaderProgram(this);
    _program->addShaderFromSourceCode(QOpenGLShader::Vertex,
        vertexShaderSource);
    _program->addShaderFromSourceCode(QOpenGLShader::Fragment,
        fragmentShaderSource);
    _program->link();
    _positionAttribute = _program->attributeLocation("posAttr");
    _colorAttribute = _program->attributeLocation("colAttr");
    _matrixUniform = _program->uniformLocation("matrix");

    CardSpecifications specifications;
    specifications.cornerDetail(8);
    specifications.cornerRadius(1.5f);
    specifications.depth(0.5f);
    CardBuilder builder(specifications);
    _cardBuffer = new CardBuffer(builder);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void MainWidget::resizeGL(int w, int h)
{
    float ratio = float(w) / float(h);
    _projection.setToIdentity();
    _projection.perspective(60.0f, ratio, 1.0f, 100.0f);
    glViewport(0, 0, w, h);
}

void MainWidget::paintGL()
{
    QMatrix4x4 matrix = _projection;
    matrix.translate(0.0f, 0.0f, -20.0f);
    matrix.rotate(_rotation, 0.0f, 1.0f, 0.0f);
    _program->bind();
    _program->setUniformValue(_matrixUniform, matrix);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableVertexAttribArray(_positionAttribute);
    glEnableVertexAttribArray(_colorAttribute);

    _cardBuffer->bind(_positionAttribute, _colorAttribute);
    _cardBuffer->drawMiddle();

    if (_rotation > 90.0f || _rotation < -90.0f)
        _cardBuffer->drawBottom();
    else
        _cardBuffer->drawTop();

    glDisableVertexAttribArray(_colorAttribute);
    glDisableVertexAttribArray(_positionAttribute);

    _program->release();
}

void MainWidget::mousePressEvent(QMouseEvent* event)
{
    qDebug() << event->x() << event->y();
}

void MainWidget::onTimer()
{
    _rotation += 1.5f;

    if (_rotation > 180.0f)
        _rotation -= 360.0f;

    updateGL();
}

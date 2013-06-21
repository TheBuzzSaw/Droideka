#include "MainWidget.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QImage>

MainWidget::MainWidget(QWidget* parent) : QGLWidget(parent)
{
    _program = 0;
    _rotation = 0.0;
}

MainWidget::~MainWidget()
{
    deleteTexture(_frontTexture);
    deleteTexture(_backTexture);
    delete _cardBuffer;
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(25);

    const char* vertexShaderSource =
        "attribute highp vec4 position;\n"
        "attribute lowp vec2 tc;\n"
        "varying lowp vec2 vtc;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   vtc = tc;\n"
        "   gl_Position = matrix * position;\n"
        "}\n";

    const char* fragmentShaderSource =
        "uniform sampler2D texture;\n"
        "varying lowp vec2 vtc;\n"
        "void main() {\n"
        "   gl_FragColor = texture2D(texture, vtc);\n"
        "}\n";

    _program = new QOpenGLShaderProgram(this);
    _program->addShaderFromSourceCode(QOpenGLShader::Vertex,
        vertexShaderSource);
    _program->addShaderFromSourceCode(QOpenGLShader::Fragment,
        fragmentShaderSource);
    _program->link();
    _positionAttribute = _program->attributeLocation("position");
    _textureAttribute = _program->attributeLocation("tc");
    _matrixUniform = _program->uniformLocation("matrix");
    _textureUniform = _program->uniformLocation("texture");

    _frontTexture = bindTexture(QImage("../localuprising.gif"));
    _backTexture = bindTexture(QImage("../liberation.gif"));

    CardSpecifications specifications;
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
    _projection.setToIdentity();
    _projection.perspective(60.0f, ratio, 1.0f, 100.0f);
    glViewport(0, 0, w, h);
}

void MainWidget::paintGL()
{
    QMatrix4x4 matrix = _projection;
    matrix.translate(0.0f, 0.0f, -12.0f);
    matrix.rotate(_rotation, 0.0f, 1.0f, 0.0f);

    _program->bind();
    _program->setUniformValue(_matrixUniform, matrix);
    _program->setUniformValue(_textureUniform, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableVertexAttribArray(_positionAttribute);
    glEnableVertexAttribArray(_textureAttribute);

    _cardBuffer->bind(_positionAttribute, _textureAttribute);
    _cardBuffer->drawMiddle();

    if (_rotation > 90.0f || _rotation < -90.0f)
    {
        glBindTexture(GL_TEXTURE_2D, _backTexture);
        _cardBuffer->drawBottom();
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, _frontTexture);
        _cardBuffer->drawTop();
    }

    glDisableVertexAttribArray(_textureAttribute);
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

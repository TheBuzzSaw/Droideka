#include "MainWidget.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QDir>

MainWidget::MainWidget(QWidget* parent) : QGLWidget(parent)
{
    _program = 0;
    _rotation = 0.0;

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
        "uniform bool enableTexture;\n"
        "varying lowp vec2 vtc;\n"
        "void main() {\n"
        "   vec4 result = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "   if (enableTexture) result = texture2D(texture, vtc);\n"
        "   gl_FragColor = result;\n"
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
    _enableTextureUniform = _program->uniformLocation("enableTexture");

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
    _program->setUniformValue(_enableTextureUniform, false);
    _cardBuffer->drawMiddle();
    _program->setUniformValue(_enableTextureUniform, true);

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

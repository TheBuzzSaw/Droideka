#include "MainWidget.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

MainWidget::MainWidget(QWidget* parent) : QGLWidget(parent),
    _cardBuilder(CardSpecifications())
{
    _program = 0;
    _rotation = 0.0;
}

MainWidget::~MainWidget()
{
}

void MainWidget::initializeGL()
{
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
        //"   gl_FragColor = col;\n"
            "   gl_FragColor = vec4(1.0, 0.5, 0.0, 1.0);\n"
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
    matrix.rotate(_rotation, 0.0f, 0.0f, 1.0f);
    _program->bind();
    _program->setUniformValue(_matrixUniform, matrix);

    glClear(GL_COLOR_BUFFER_BIT);

    glVertexAttribPointer(_positionAttribute, 3, GL_FLOAT, GL_FALSE, 0,
        _cardBuilder.vertices().constData());
    glVertexAttribPointer(_colorAttribute, 2, GL_FLOAT, GL_FALSE, 0,
        _cardBuilder.textureCoordinates().constData());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, _cardBuilder.topIndices().size(),
        GL_UNSIGNED_SHORT, _cardBuilder.topIndices().constData());

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    _program->release();
}

void MainWidget::mousePressEvent(QMouseEvent* event)
{
    qDebug() << event->x() << event->y();
}

void MainWidget::onTimer()
{
    _rotation += 1.0f;

    if (_rotation > 180.0f)
    {
        _rotation -= 360.0f;
        qDebug() << "reset rotation";
    }

    updateGL();
}

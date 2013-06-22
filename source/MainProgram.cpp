#include "MainProgram.hpp"

MainProgram::MainProgram()
{
    initializeOpenGLFunctions();

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
#ifndef Q_OS_LINUX
        // This produces a warning in Linux:
        // warning C7022: unrecognized profile specifier "precision"
        "precision highp float;\n"
#endif
        "uniform bool enableTexture;\n"
        "uniform sampler2D texture;\n"
        "uniform lowp vec4 highlight;\n"
        "varying lowp vec2 vtc;\n"
        "void main() {\n"
        "   vec4 result = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "   if (enableTexture) result = texture2D(texture, vtc);\n"
        "   gl_FragColor = result + highlight;\n"
        "}\n";

    _program.addShaderFromSourceCode(QOpenGLShader::Vertex,
        vertexShaderSource);
    _program.addShaderFromSourceCode(QOpenGLShader::Fragment,
        fragmentShaderSource);
    _program.link();
    _positionAttribute = _program.attributeLocation("position");
    _textureAttribute = _program.attributeLocation("tc");
    _matrixUniform = _program.uniformLocation("matrix");
    _textureUniform = _program.uniformLocation("texture");
    _highlightUniform = _program.uniformLocation("highlight");
    _enableTextureUniform = _program.uniformLocation("enableTexture");

    _program.setUniformValue(_textureUniform, 0);
    enableTexture(true);
    setHighlight(QVector4D());
}

MainProgram::~MainProgram()
{
}

void MainProgram::bind()
{
    _program.bind();
    glEnableVertexAttribArray(_positionAttribute);
    glEnableVertexAttribArray(_textureAttribute);
}

void MainProgram::release()
{
    glDisableVertexAttribArray(_textureAttribute);
    glDisableVertexAttribArray(_positionAttribute);
    _program.release();
}

void MainProgram::setMatrix(const QMatrix4x4& matrix)
{
    _program.setUniformValue(_matrixUniform, matrix);
}

void MainProgram::enableTexture(bool enable)
{
    _program.setUniformValue(_enableTextureUniform, enable);
}

void MainProgram::setHighlight(const QVector4D &highlight)
{
    _program.setUniformValue(_highlightUniform, highlight);
}

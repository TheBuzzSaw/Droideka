#include "MainProgram.hpp"

MainProgram::MainProgram()
{
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
        "precision highp float;\n"
        "uniform bool enableTexture;\n"
        "uniform sampler2D texture;\n"
        "varying lowp vec2 vtc;\n"
        "void main() {\n"
        "   vec4 result = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "   if (enableTexture) result = texture2D(texture, vtc);\n"
        "   gl_FragColor = result;\n"
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
    _enableTextureUniform = _program.uniformLocation("enableTexture");

    _program.setUniformValue(_textureUniform, 0);
}

MainProgram::~MainProgram()
{
}

void MainProgram::bind()
{
    _program.bind();
}

void MainProgram::release()
{
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

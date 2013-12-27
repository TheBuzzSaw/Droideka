#include "BasicProgram.hpp"

BasicProgram::BasicProgram()
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
#ifdef Q_OS_WIN
        // This produces a warning in Linux:
        // warning C7022: unrecognized profile specifier "precision"

        // This explodes in OSX. Apparently, only Windows demands it.
        //"precision highp float;\n"
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

BasicProgram::~BasicProgram()
{
}

void BasicProgram::bind()
{
    _program.bind();
    glEnableVertexAttribArray(_positionAttribute);
    glEnableVertexAttribArray(_textureAttribute);
}

void BasicProgram::release()
{
    glDisableVertexAttribArray(_textureAttribute);
    glDisableVertexAttribArray(_positionAttribute);
    _program.release();
}

void BasicProgram::setMatrix(const QMatrix4x4& matrix)
{
    _program.setUniformValue(_matrixUniform, matrix);
}

void BasicProgram::enableTexture(bool enable)
{
    _program.setUniformValue(_enableTextureUniform, enable);
}

void BasicProgram::setHighlight(const QVector4D& highlight)
{
    _program.setUniformValue(_highlightUniform, highlight);
}

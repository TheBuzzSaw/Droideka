#ifndef MAINPROGRAM_HPP
#define MAINPROGRAM_HPP

#include <QMatrix4x4>
#include <QVector4D>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class BasicProgram
{
public:
    BasicProgram(QOpenGLFunctions& functions);
    virtual ~BasicProgram();

    inline GLuint positionAttribute() const { return _positionAttribute; }
    inline GLuint textureAttribute() const { return _textureAttribute; }

    void open();
    void close();
    void setMatrix(const QMatrix4x4& matrix);
    void enableTexture(bool enable);
    void setHighlight(const QVector4D& highlight);

private:
    QOpenGLFunctions& _functions;
    QOpenGLShaderProgram _program;

    GLuint _positionAttribute;
    GLuint _textureAttribute;
    GLuint _matrixUniform;
    GLuint _textureUniform;
    GLuint _highlightUniform;
    GLuint _enableTextureUniform;
};

#endif

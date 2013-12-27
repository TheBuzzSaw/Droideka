#ifndef MAINPROGRAM_HPP
#define MAINPROGRAM_HPP

#include <QMatrix4x4>
#include <QVector4D>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class BasicProgram : protected QOpenGLFunctions
{
public:
    BasicProgram();
    virtual ~BasicProgram();

    inline GLuint positionAttribute() const { return _positionAttribute; }
    inline GLuint textureAttribute() const { return _textureAttribute; }

    void bind();
    void release();
    void setMatrix(const QMatrix4x4& matrix);
    void enableTexture(bool enable);
    void setHighlight(const QVector4D& highlight);

private:
    QOpenGLShaderProgram _program;

    GLuint _positionAttribute;
    GLuint _textureAttribute;
    GLuint _matrixUniform;
    GLuint _textureUniform;
    GLuint _highlightUniform;
    GLuint _enableTextureUniform;
};

#endif

#ifndef BASICBUILDER_HPP
#define BASICBUILDER_HPP

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLFunctions>

class BasicBuilder
{
public:
    BasicBuilder();
    BasicBuilder(BasicBuilder&& other);
    ~BasicBuilder();

    BasicBuilder& operator=(BasicBuilder&& other);

    int vertexCount() const;

    void reserve(int vertexCount);
    void add(QVector3D position, QVector2D textureCoordinate);
    void bufferData(QOpenGLFunctions& functions,
        GLenum usage = GL_STATIC_DRAW) const;

private:
    BasicBuilder(const BasicBuilder&) = delete;
    BasicBuilder& operator=(const BasicBuilder&) = delete;

    QVector<GLfloat> _values;
};

#endif

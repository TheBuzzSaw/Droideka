#include "TableBuffer.hpp"
#include <QDebug>

TableBuffer::TableBuffer(QOpenGLFunctions& functions)
{
    BasicBuilder builder;

    const float P = 500.0f;
    const float T = 100.0f;

    builder.add(QVector3D(P, P, 0.0f), QVector2D(T, T));
    builder.add(QVector3D(P, -P, 0.0f), QVector2D(T, -T));
    builder.add(QVector3D(-P, -P, 0.0f), QVector2D(-T, -T));
    builder.add(QVector3D(-P, P, 0.0f), QVector2D(-T, T));

    _object = BasicBufferObject(functions, builder);
}

TableBuffer::~TableBuffer()
{
}

void TableBuffer::draw(const BasicProgram& program)
{
    _object.bind(program);
    glDrawArrays(GL_TRIANGLE_FAN, 0, _object.vertexCount());
}

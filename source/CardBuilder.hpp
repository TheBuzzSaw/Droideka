#ifndef CARDBUILDER_HPP
#define CARDBUILDER_HPP

#include "CardSpecifications.hpp"
#include "BasicBufferObject.hpp"
#include <QOpenGLFunctions>

class CardBuilder
{
public:
    CardBuilder(const CardSpecifications& specifications);
    ~CardBuilder();

    inline const CardSpecifications& specifications() const
    {
        return _specifications;
    }

    BasicBufferObject bufferObject(QOpenGLFunctions& functions) const;

    inline const QVector<GLushort>& topIndices() const
    {
        return _topIndices;
    }

    inline const QVector<GLushort>& middleIndices() const
    {
        return _middleIndices;
    }

    inline const QVector<GLushort>& bottomIndices() const
    {
        return _bottomIndices;
    }

private:
    CardSpecifications _specifications;

    QVector<GLfloat> _vertices;
    QVector<GLfloat> _textureCoordinates;
    QVector<GLushort> _topIndices;
    QVector<GLushort> _middleIndices;
    QVector<GLushort> _bottomIndices;

    void addVertex(float x, float y, float s, float t);
    void addTriangle(GLushort a, GLushort b, GLushort c);
    void addTriangles(GLushort a, GLushort b, GLushort c);
    void addQuad(GLushort a, GLushort b, GLushort c, GLushort d);
    void addQuads(GLushort a, GLushort b, GLushort c, GLushort d);
};

#endif

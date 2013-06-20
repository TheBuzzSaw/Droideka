#include "CardBuilder.hpp"
#include <cmath>

CardBuilder::CardBuilder(const CardSpecifications& specifications)
    : _specifications(specifications)
{
    float w = _specifications.width() / 2.0f;
    float h = _specifications.height() / 2.0f;
    float cr = _specifications.cornerRadius();
    int cd = _specifications.cornerDetail();

    int vertexCount = 8 * cd + 16;
    _vertices.reserve(vertexCount * 3);
    _textureCoordinates.reserve(vertexCount * 2);

    // upper left corner
    addVertex(cr - w, h - cr, cr / _specifications.width(),
        cr / _specifications.height());

    addVertex(-w, h - cr, 0.0f, cr / _specifications.height());

    float theta = 90.0f / float(cd);
    for (int i = 1; i < cd; ++i)
    {
        float radians = float(i) * theta * (3.1415926535898f / 180.0f);
        float dx = cr * cos(radians);
        float dy = cr * sin(radians);

        addVertex(cr - w - dx, h  - cr + dy,
            (cr - dx) / _specifications.width(),
            (cr - dy) / _specifications.height());
    }

    addVertex(cr - w, h, cr / _specifications.width(), 0.0f);

    // upper right corner
    addVertex(-_vertices[0], _vertices[1],
        1.0f - _textureCoordinates[0],
        _textureCoordinates[1]);

    int previousVertex = _vertices.size() - 6;
    int previousTexture = _textureCoordinates.size() - 4;

    int mirrorVertex = _vertices.size() - 12;
    int mirrorTexture = _textureCoordinates.size() - 8;

    for (int i = 0; i <= cd; ++i)
    {
        addVertex(-_vertices[mirrorVertex], _vertices[mirrorVertex + 1],
            1.0f - _textureCoordinates[mirrorTexture],
            _textureCoordinates[mirrorTexture + 1]);

        mirrorVertex -= 6;
        mirrorTexture -= 4;
    }

    // lower right corner
    addVertex(_vertices[previousVertex], -_vertices[previousVertex + 1],
        _textureCoordinates[previousTexture],
        1.0f - _textureCoordinates[previousTexture + 1]);

    previousVertex = _vertices.size() - 6;
    previousTexture = _textureCoordinates.size() - 4;

    mirrorVertex = _vertices.size() - 12;
    mirrorTexture = _textureCoordinates.size() - 8;

    for (int i = 0; i <= cd; ++i)
    {
        addVertex(_vertices[mirrorVertex], -_vertices[mirrorVertex + 1],
            _textureCoordinates[mirrorTexture],
            1.0f - _textureCoordinates[mirrorTexture + 1]);

        mirrorVertex -= 6;
        mirrorTexture -= 4;
    }

    // lower left corner
    addVertex(-_vertices[previousVertex], _vertices[previousVertex + 1],
        1.0f - _textureCoordinates[previousTexture],
        _textureCoordinates[previousTexture + 1]);

    previousVertex = _vertices.size() - 6;
    previousTexture = _textureCoordinates.size() - 4;

    mirrorVertex = _vertices.size() - 12;
    mirrorTexture = _textureCoordinates.size() - 8;

    for (int i = 0; i <= cd; ++i)
    {
        addVertex(-_vertices[mirrorVertex], _vertices[mirrorVertex + 1],
            1.0f - _textureCoordinates[mirrorTexture],
            _textureCoordinates[mirrorTexture + 1]);

        mirrorVertex -= 6;
        mirrorTexture -= 4;
    }
    // texture correction
    for (int i = 0; i < vertexCount; ++i)
    {
        int index = i * 2 + 1;
        _textureCoordinates[index] = 1.0f - _textureCoordinates[index];
    }

    // index creation
    int triangleCount = 16 * cd + 28;
    int middleTriangleCount = 8 * cd + 8;
    int topTriangleCount = (triangleCount - middleTriangleCount) / 2;

    _topIndices.reserve(topTriangleCount * 3);
    _middleIndices.reserve(middleTriangleCount * 3);
    _bottomIndices.reserve(topTriangleCount * 3);

    GLushort corners[5];
    int cornerSize = 2 * cd + 4;

    for (int i = 0; i < 5; ++i)
        corners[i] = cornerSize * i;

    for (int i = 0; i < 4; ++i)
    {
        int i4 = (i + 1) % 4;
        addQuads(corners[i], corners[i + 1] - 2, corners[i4] + 2, corners[i4]);
        addQuad(corners[i + 1] - 2, corners[i + 1] - 1, corners[i4] + 3,
            corners[i4] + 2);

        for (int j = 0; j < cd; ++j)
        {
            int k = 2 * (j + 1);
            addTriangles(corners[i], corners[i] + k, corners[i] + k + 2);
            addQuad(corners[i] + k, corners[i] + k + 1, corners[i] + k + 3,
                corners[i] + k + 2);
        }
    }

    addQuads(corners[0], corners[1], corners[2], corners[3]);
}

CardBuilder::~CardBuilder()
{
}

void CardBuilder::addVertex(float x, float y, float s, float t)
{
    float d = _specifications.depth() / 2.0f;

    _vertices.append(x);
    _vertices.append(y);
    _vertices.append(d);

    _vertices.append(x);
    _vertices.append(y);
    _vertices.append(-d);

    _textureCoordinates.append(s);
    _textureCoordinates.append(t);

    _textureCoordinates.append(1.0f - s);
    _textureCoordinates.append(t);
}

void CardBuilder::addTriangle(GLushort a, GLushort b, GLushort c)
{
    _middleIndices.append(a);
    _middleIndices.append(b);
    _middleIndices.append(c);
}

void CardBuilder::addTriangles(GLushort a, GLushort b, GLushort c)
{
    _topIndices.append(a);
    _topIndices.append(b);
    _topIndices.append(c);

    _bottomIndices.append(c + 1);
    _bottomIndices.append(b + 1);
    _bottomIndices.append(a + 1);
}

void CardBuilder::addQuad(GLushort a, GLushort b, GLushort c, GLushort d)
{
    addTriangle(a, b, c);
    addTriangle(a, c, d);
}

void CardBuilder::addQuads(GLushort a, GLushort b, GLushort c, GLushort d)
{
    addTriangles(a, b, c);
    addTriangles(a, c, d);
}

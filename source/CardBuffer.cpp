#include "CardBuffer.hpp"

CardBuffer::CardBuffer(const CardBuilder& builder)
    : _specifications(builder.specifications())
{
    initializeOpenGLFunctions();
    glGenBuffers(BufferCount, _buffers);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[Vertex]);
    glBufferData(GL_ARRAY_BUFFER, builder.vertices().size() * sizeof(GLfloat),
        builder.vertices().constData(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[Texture]);
    glBufferData(GL_ARRAY_BUFFER,
        builder.textureCoordinates().size() * sizeof(GLfloat),
        builder.textureCoordinates().constData(),
        GL_STATIC_DRAW);

    _topCount = builder.topIndices().size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[TopIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        _topCount * sizeof(GLushort),
        builder.topIndices().constData(),
        GL_STATIC_DRAW);

    _middleCount = builder.middleIndices().size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[MiddleIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        _middleCount * sizeof(GLushort),
        builder.middleIndices().constData(),
        GL_STATIC_DRAW);

    _bottomCount = builder.bottomIndices().size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[BottomIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        _bottomCount * sizeof(GLushort),
        builder.bottomIndices().constData(),
        GL_STATIC_DRAW);
}

CardBuffer::~CardBuffer()
{
    glDeleteBuffers(BufferCount, _buffers);
}

void CardBuffer::drawTop()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[TopIndex]);
    glDrawElements(GL_TRIANGLES, _topCount, GL_UNSIGNED_SHORT, 0);
}

void CardBuffer::drawMiddle()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[MiddleIndex]);
    glDrawElements(GL_TRIANGLES, _middleCount, GL_UNSIGNED_SHORT, 0);
}

void CardBuffer::drawBottom()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[BottomIndex]);
    glDrawElements(GL_TRIANGLES, _bottomCount, GL_UNSIGNED_SHORT, 0);
}

void CardBuffer::bind(GLuint vertexLocation, GLuint textureLocation)
{
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[Vertex]);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[Texture]);
    glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

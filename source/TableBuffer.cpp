#include "TableBuffer.hpp"

TableBuffer::TableBuffer()
{
    initializeOpenGLFunctions();
    glGenBuffers(BufferCount, _buffers);

    GLfloat vertices[] = {
        500.0f, 500.0f,
        500.0f, -500.0f,
        -500.0f, -500.0f,
        -500.0f, 500.0f,
        };

    GLfloat textureCoordinates[] = {
        100.0f, 100.0f,
        100.0f, -100.0f,
        -100.0f, -100.0f,
        -100.0f, 100.0f,
        };

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[Vertex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[Texture]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates),
        textureCoordinates, GL_STATIC_DRAW);
}

TableBuffer::~TableBuffer()
{
}

void TableBuffer::bind(GLuint vertexLocation, GLuint textureLocation)
{
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[Vertex]);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[Texture]);
    glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void TableBuffer::draw()
{
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

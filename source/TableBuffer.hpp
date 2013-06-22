#ifndef TABLEBUFFER_HPP
#define TABLEBUFFER_HPP

#include <QOpenGLFunctions>

class TableBuffer : protected QOpenGLFunctions
{
public:
    TableBuffer();
    virtual ~TableBuffer();

    void bind(GLuint vertexLocation, GLuint textureLocation);
    void draw();

private:
    static const int BufferCount = 2;
    static const int Vertex = 0;
    static const int Texture = 1;

    GLuint _buffers[BufferCount];
};

#endif

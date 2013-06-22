#ifndef CARDBUFFER_HPP
#define CARDBUFFER_HPP

#include "CardBuilder.hpp"
#include <QOpenGLFunctions>

class CardBuffer : protected QOpenGLFunctions
{
public:
    CardBuffer(const CardBuilder& builder);
    virtual ~CardBuffer();

    inline const CardSpecifications& specifications() const
    {
        return _specifications;
    }

    void bind(GLuint vertexLocation, GLuint textureLocation);
    void drawTop();
    void drawMiddle();
    void drawBottom();

private:
    static const int BufferCount = 5;
    static const int Vertex = 0;
    static const int Texture = 1;
    static const int TopIndex = 2;
    static const int MiddleIndex = 3;
    static const int BottomIndex = 4;

    CardSpecifications _specifications;
    GLuint _buffers[BufferCount];
    GLsizei _topCount;
    GLsizei _middleCount;
    GLsizei _bottomCount;
};

#endif

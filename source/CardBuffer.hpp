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

    void bind(const BasicProgram& program);
    void drawTop();
    void drawMiddle();
    void drawBottom();

private:
    static const int BufferCount = 3;
    static const int TopIndex = 0;
    static const int MiddleIndex = 1;
    static const int BottomIndex = 2;

    CardSpecifications _specifications;
    BasicBufferObject _object;
    GLuint _buffers[BufferCount];
    GLsizei _topCount;
    GLsizei _middleCount;
    GLsizei _bottomCount;
};

#endif

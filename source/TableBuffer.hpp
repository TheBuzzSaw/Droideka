#ifndef TABLEBUFFER_HPP
#define TABLEBUFFER_HPP

#include "BasicBufferObject.hpp"

class TableBuffer
{
public:
    TableBuffer(QOpenGLFunctions& functions);
    virtual ~TableBuffer();

    void draw(const BasicProgram& program);

private:
    BasicBufferObject _object;
};

#endif

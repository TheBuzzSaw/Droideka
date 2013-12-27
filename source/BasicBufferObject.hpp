#ifndef BASICBUFFEROBJECT_HPP
#define BASICBUFFEROBJECT_HPP

#include "BasicBuilder.hpp"
#include "BasicProgram.hpp"

class BasicBufferObject
{
public:
    BasicBufferObject();
    BasicBufferObject(BasicBufferObject&& other);
    BasicBufferObject(QOpenGLFunctions& functions, const BasicBuilder& builder);
    ~BasicBufferObject();

    BasicBufferObject& operator=(BasicBufferObject&& other);

    inline int vertexCount() const { return _vertexCount; }

    void bind(const BasicProgram& program);

private:
    BasicBufferObject(const BasicBufferObject&) = delete;
    BasicBufferObject& operator=(const BasicBufferObject&) = delete;

    QOpenGLFunctions* _functions;
    GLuint _object;
    int _vertexCount;
};

#endif

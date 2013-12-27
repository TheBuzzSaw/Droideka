#include "BasicBufferObject.hpp"

static constexpr GLvoid* offset(size_t offset)
{
    return (GLfloat*)0 + offset;
}

BasicBufferObject::BasicBufferObject()
    : _functions(nullptr)
    , _object(0)
    , _vertexCount(0)
{
}

BasicBufferObject::BasicBufferObject(BasicBufferObject&& other)
    : _functions(other._functions)
    , _object(other._object)
    , _vertexCount(other._vertexCount)
{
    other._functions = nullptr;
    other._object = 0;
    other._vertexCount = 0;
}

BasicBufferObject::BasicBufferObject(QOpenGLFunctions& functions,
    const BasicBuilder& builder)
    : _functions(&functions)
    , _object(0)
    , _vertexCount(builder.vertexCount())
{
    _functions->glGenBuffers(1, &_object);
    _functions->glBindBuffer(GL_ARRAY_BUFFER, _object);
    builder.bufferData(*_functions);
}

BasicBufferObject::~BasicBufferObject()
{
    if (_functions) _functions->glDeleteBuffers(1, &_object);
}

BasicBufferObject& BasicBufferObject::operator=(BasicBufferObject&& other)
{
    if (this != &other)
    {
        _functions = other._functions;
        _object = other._object;
        _vertexCount = other._vertexCount;

        other._functions = nullptr;
        other._object = 0;
        other._vertexCount = 0;
    }

    return *this;
}

void BasicBufferObject::bind(const BasicProgram& program)
{
    if (_functions)
    {
        const GLsizei Stride = sizeof(GLfloat) * 5;

        _functions->glBindBuffer(GL_ARRAY_BUFFER, _object);

        _functions->glVertexAttribPointer(
            program.positionAttribute(),
            3,
            GL_FLOAT,
            GL_FALSE,
            Stride,
            offset(0));

        _functions->glVertexAttribPointer(
            program.textureAttribute(),
            2,
            GL_FLOAT,
            GL_FALSE,
            Stride,
            offset(3));
    }
}

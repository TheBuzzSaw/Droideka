#include "IndexBufferObject.hpp"

IndexBufferObject::IndexBufferObject()
    : VertexBufferObject(QGLBuffer::IndexBuffer, GL_UNSIGNED_INT)
{
}

IndexBufferObject::~IndexBufferObject()
{
}

void IndexBufferObject::drawElements(GLenum inMode)
{
    bind();
    glDrawElements(inMode, mValueCount, mDataType, 0);
}

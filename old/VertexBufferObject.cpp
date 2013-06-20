#include "VertexBufferObject.hpp"
#include <cassert>

VertexBufferObject::VertexBufferObject(QGLBuffer::Type inBufferType,
    GLenum inDataType, QGLBuffer::UsagePattern inUsage)
    : mBuffer(inBufferType), mDataType(inDataType), mBytesPerValue(0),
      mValuesPerVertex(0), mVertexCount(0), mValueCount(0), mClientState(0)
{
    mBuffer.create();
    mBuffer.setUsagePattern(inUsage);

    switch (mDataType)
    {
    case GL_FLOAT:
        mBytesPerValue = sizeof(GLfloat);
        break;

    case GL_UNSIGNED_BYTE:
        mBytesPerValue = sizeof(GLubyte);
        break;

    case GL_UNSIGNED_SHORT:
        mBytesPerValue = sizeof(GLushort);
        break;

    case GL_UNSIGNED_INT:
        mBytesPerValue = sizeof(GLuint);
        break;

    default:
        mDataType = GL_FLOAT;
        mBytesPerValue = sizeof(GLfloat);
    }
}

VertexBufferObject::~VertexBufferObject()
{
    mBuffer.destroy();
}

void VertexBufferObject::loadData(const GLvoid *inData, GLuint inCount,
    GLuint inValuesPerVertex)
{
    mVertexCount = inCount;
    mValuesPerVertex = inValuesPerVertex;

    bind();
    mValueCount = mVertexCount * mValuesPerVertex;
    mBuffer.allocate(inData, mValueCount * mBytesPerValue);
}

void VertexBufferObject::draw(GLenum inMode)
{
    vertexPointer();
    glDrawArrays(inMode, 0, mVertexCount);
    disableClientState();
}

void VertexBufferObject::vertexPointer()
{
    assert(mClientState == 0);

    mClientState = GL_VERTEX_ARRAY;
    glEnableClientState(mClientState);
    bind();
    glVertexPointer(mValuesPerVertex, mDataType, 0, 0);
}

void VertexBufferObject::textureCoordinatePointer()
{
    assert(mClientState == 0);

    mClientState = GL_TEXTURE_COORD_ARRAY;
    glEnableClientState(mClientState);
    bind();
    glTexCoordPointer(mValuesPerVertex, mDataType, 0, 0);
}

void VertexBufferObject::disableClientState()
{
    assert(mClientState != 0);

    glDisableClientState(mClientState);
    mClientState = 0;
}

#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP

#include <QGLBuffer>

class VertexBufferObject
{
public:
    VertexBufferObject(QGLBuffer::Type inBufferType = QGLBuffer::VertexBuffer,
        GLenum inDataType = GL_FLOAT,
        QGLBuffer::UsagePattern inUsage = QGLBuffer::StaticDraw);
    virtual ~VertexBufferObject();

    void loadData(const GLvoid* inData, GLuint inCount,
        GLuint inValuesPerVertex = 1);

    void vertexPointer();
    void textureCoordinatePointer();
    void disableClientState();

protected:
    inline void bind() { mBuffer.bind(); }

    QGLBuffer mBuffer;
    GLenum mDataType;
    GLuint mBytesPerDatum;
    GLuint mValuesPerVertex;
    GLuint mVertexCount;
    GLuint mValueCount;
    GLenum mClientState;
};

#endif

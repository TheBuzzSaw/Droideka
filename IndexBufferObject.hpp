#ifndef INDEXBUFFEROBJECT_HPP
#define INDEXBUFFEROBJECT_HPP

#include "VertexBufferObject.hpp"

class IndexBufferObject : public VertexBufferObject
{
public:
    IndexBufferObject();
    virtual ~IndexBufferObject();

    void drawElements(GLenum inMode = GL_TRIANGLES);
};

#endif

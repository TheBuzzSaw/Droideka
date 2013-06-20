#ifndef TABLEMODEL_HPP
#define TABLEMODEL_HPP

#include "VertexBufferObject.hpp"

class TableModel
{
public:
    TableModel(GLuint inTexture);
    virtual ~TableModel();

    void draw();

private:
    GLuint mTexture;
    VertexBufferObject mVertexBuffer;
    VertexBufferObject mTextureBuffer;
};

#endif

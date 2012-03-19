#ifndef CARDMODEL_HPP
#define CARDMODEL_HPP

#include "IndexBufferObject.hpp"

class CardModel
{
public:
    CardModel();
    virtual ~CardModel();

    void drawFront(GLuint inTexture);
    void drawBack(GLuint inTexture);
    void drawEdge();

    void assemble();

private:
    VertexBufferObject mVertexBuffer;
    VertexBufferObject mTextureBuffer;
    IndexBufferObject mTopIndexBuffer;
    IndexBufferObject mMiddleIndexBuffer;
    IndexBufferObject mBottomIndexBuffer;
};

#endif

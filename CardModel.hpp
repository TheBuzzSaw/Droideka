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

    inline float width() const { return mWidth; }
    inline float height() const { return mHeight; }
    inline float depth() const { return mDepth; }

private:
    void assemble();

    float mWidth;
    float mHeight;
    float mDepth;

    VertexBufferObject mVertexBuffer;
    VertexBufferObject mTextureBuffer;
    IndexBufferObject mTopIndexBuffer;
    IndexBufferObject mMiddleIndexBuffer;
    IndexBufferObject mBottomIndexBuffer;
};

#endif

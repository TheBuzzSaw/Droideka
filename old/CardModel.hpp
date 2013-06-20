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
    void assembleSimple();
    void assembleDetailed();

    float mWidth;
    float mHeight;
    float mDepth;
    float mCornerRadius;
    int mDetail;

    void addVertex(float inX, float inY, float inS, float inT);

    GLfloat* mVertices;
    GLfloat* mVertex;
    GLfloat* mTextureCoordinates;
    GLfloat* mTextureCoordinate;

    void addTriangle(GLuint inA, GLuint inB, GLuint inC);
    void addTriangles(GLuint inA, GLuint inB, GLuint inC);
    void addQuad(GLuint inA, GLuint inB, GLuint inC, GLuint inD);
    void addQuads(GLuint inA, GLuint inB, GLuint inC, GLuint inD);

    GLuint* mTopIndices;
    GLuint* mTopIndex;
    GLuint* mMiddleIndices;
    GLuint* mMiddleIndex;
    GLuint* mBottomIndices;
    GLuint* mBottomIndex;

    VertexBufferObject mVertexBuffer;
    VertexBufferObject mTextureBuffer;
    IndexBufferObject mTopIndexBuffer;
    IndexBufferObject mMiddleIndexBuffer;
    IndexBufferObject mBottomIndexBuffer;
};

#endif

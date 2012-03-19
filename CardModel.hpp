#ifndef CARDMODEL_HPP
#define CARDMODEL_HPP

#include <QGLBuffer>

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
    QGLBuffer mVertexBuffer;
    QGLBuffer mTextureBuffer;
    QGLBuffer mTopIndexBuffer;
    QGLBuffer mMiddleIndexBuffer;
    QGLBuffer mBottomIndexBuffer;
};

#endif

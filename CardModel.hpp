#ifndef CARDMODEL_HPP
#define CARDMODEL_HPP

#include <QGLBuffer>

class CardModel
{
public:
    CardModel();
    virtual ~CardModel();

    void drawFront();
    void drawBack();
    void drawEdge();

private:
    QGLBuffer mVertexBuffer;
    QGLBuffer mTextureBuffer;
    QGLBuffer mTopIndexBuffer;
    QGLBuffer mMiddleIndexBuffer;
    QGLBuffer mBottomIndexBuffer;
};

#endif

#include "CardModel.hpp"

CardModel::CardModel() : mVertexBuffer(QGLBuffer::VertexBuffer),
    mTextureBuffer(QGLBuffer::VertexBuffer),
    mTopIndexBuffer(QGLBuffer::IndexBuffer),
    mMiddleIndexBuffer(QGLBuffer::IndexBuffer),
    mBottomIndexBuffer(QGLBuffer::IndexBuffer)
{
    mVertexBuffer.create();
    mTextureBuffer.create();
    mTopIndexBuffer.create();
    mMiddleIndexBuffer.create();
    mBottomIndexBuffer.create();
}

CardModel::~CardModel()
{
    mVertexBuffer.destroy();
    mTextureBuffer.destroy();
    mTopIndexBuffer.destroy();
    mMiddleIndexBuffer.destroy();
    mBottomIndexBuffer.destroy();
}

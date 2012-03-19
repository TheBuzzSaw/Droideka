#include "CardModel.hpp"
#include <QDebug>

CardModel::CardModel() : mVertexBuffer(QGLBuffer::VertexBuffer),
    mTextureBuffer(QGLBuffer::VertexBuffer),
    mTopIndexBuffer(QGLBuffer::IndexBuffer),
    mMiddleIndexBuffer(QGLBuffer::IndexBuffer),
    mBottomIndexBuffer(QGLBuffer::IndexBuffer)
{
}

CardModel::~CardModel()
{
    mVertexBuffer.destroy();
    mTextureBuffer.destroy();
    mTopIndexBuffer.destroy();
    mMiddleIndexBuffer.destroy();
    mBottomIndexBuffer.destroy();
}

void CardModel::drawFront(GLuint inTexture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, inTexture);

    glEnableClientState(GL_VERTEX_ARRAY);
    mVertexBuffer.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    mTextureBuffer.bind();
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    mTopIndexBuffer.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
}

void CardModel::drawBack(GLuint inTexture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, inTexture);

    glEnableClientState(GL_VERTEX_ARRAY);
    mVertexBuffer.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    mTextureBuffer.bind();
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    mBottomIndexBuffer.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
}

void CardModel::drawEdge()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    mVertexBuffer.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);

    mMiddleIndexBuffer.bind();
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void CardModel::assemble()
{
    float inWidth = 6.3f;
    float inHeight = 8.8f;

    float w = inWidth  / 2.0f;
    float h = inHeight / 2.0f;
    float d = 0.05 / 2.0f;

    GLfloat points[24] = {
        +w, +h, +d,
        +w, -h, +d,
        -w, -h, +d,
        -w, +h, +d,
        +w, +h, -d,
        +w, -h, -d,
        -w, -h, -d,
        -w, +h, -d
        };

    mVertexBuffer.create();
    mVertexBuffer.bind();
    mVertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mVertexBuffer.allocate(points, sizeof(points));

    GLfloat textureCoordinates[16] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
        };

    float ratio = inWidth / inHeight;
    float adjustment = 490.0f / 512.0f; // card image size adjustment
    for (size_t i = 0; i < 8; ++i)
    {
        break;
        size_t index = i * 2;
        // It is assumed that the card is taller than it is wide.
        textureCoordinates[index] *= ratio * adjustment;
        textureCoordinates[index + 1] *= adjustment;
    }

    mTextureBuffer.create();
    mTextureBuffer.bind();
    mTextureBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mTextureBuffer.allocate(textureCoordinates, sizeof(textureCoordinates));

    GLuint topIndices[6] = { 0, 1, 2, 0, 2, 3 };

    GLuint middleIndices[24] = {
        1, 0, 4, 1, 4, 5, // right
        3, 2, 6, 3, 6, 7, // left
        2, 1, 5, 2, 5, 6, // front
        0, 3, 7, 0, 7, 4  // back
        };

    GLuint bottomIndices[6] = { 7, 6, 5, 7, 5, 4 };

    mTopIndexBuffer.create();
    mTopIndexBuffer.bind();
    mTopIndexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mTopIndexBuffer.allocate(topIndices, sizeof(topIndices));

    mMiddleIndexBuffer.create();
    mMiddleIndexBuffer.bind();
    mMiddleIndexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mMiddleIndexBuffer.allocate(middleIndices, sizeof(middleIndices));

    mBottomIndexBuffer.create();
    mBottomIndexBuffer.bind();
    mBottomIndexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mBottomIndexBuffer.allocate(bottomIndices, sizeof(bottomIndices));
}

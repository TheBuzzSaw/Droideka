#include "CardModel.hpp"
#include <QDebug>

CardModel::CardModel()
{
    assemble();
}

CardModel::~CardModel()
{
}

void CardModel::drawFront(GLuint inTexture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, inTexture);
    mVertexBuffer.vertexPointer();
    mTextureBuffer.textureCoordinatePointer();
    mTopIndexBuffer.drawElements();
    mTextureBuffer.disableClientState();
    mVertexBuffer.disableClientState();
    glDisable(GL_TEXTURE_2D);
}

void CardModel::drawBack(GLuint inTexture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, inTexture);
    mVertexBuffer.vertexPointer();
    mTextureBuffer.textureCoordinatePointer();
    mBottomIndexBuffer.drawElements();
    mTextureBuffer.disableClientState();
    mVertexBuffer.disableClientState();
    glDisable(GL_TEXTURE_2D);
}

void CardModel::drawEdge()
{
    mVertexBuffer.vertexPointer();
    mMiddleIndexBuffer.drawElements();
    mVertexBuffer.disableClientState();
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

    mVertexBuffer.loadData(points, 8, 3);

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

    mTextureBuffer.loadData(textureCoordinates, 8, 2);

    GLuint topIndices[6] = { 0, 1, 2, 0, 2, 3 };

    mTopIndexBuffer.loadData(topIndices, 2, 3);

    GLuint middleIndices[24] = {
        1, 0, 4, 1, 4, 5, // right
        3, 2, 6, 3, 6, 7, // left
        2, 1, 5, 2, 5, 6, // front
        0, 3, 7, 0, 7, 4  // back
        };

    mMiddleIndexBuffer.loadData(middleIndices, 8, 3);

    GLuint bottomIndices[6] = { 7, 6, 5, 7, 5, 4 };

    mBottomIndexBuffer.loadData(bottomIndices, 2, 3);
}

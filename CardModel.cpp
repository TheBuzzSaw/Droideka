#include "CardModel.hpp"
#include <QDebug>
#include <cmath>

CardModel::CardModel() : mWidth(6.3f), mHeight(8.8f), mDepth(0.05f)
{
    mCornerRadius = 0.25f;
    mDetail = 4;
    //assembleSimple();
    assembleDetailed();
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

void CardModel::assembleSimple()
{
    float w = mWidth  / 2.0f;
    float h = mHeight / 2.0f;
    float d = mDepth / 2.0f;

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
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
        };

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

void CardModel::addVertex(float inX, float inY, float inS, float inT)
{
    float d = mDepth / 2.0f;

    *mVertex++ = inX;
    *mVertex++ = inY;
    *mVertex++ = d;

    *mVertex++ = inX;
    *mVertex++ = inY;
    *mVertex++ = -d;

    *mTextureCoordinate++ = inS;
    *mTextureCoordinate++ = inT;
    *mTextureCoordinate++ = 1.0f - inS;
    *mTextureCoordinate++ = inT;
}

void CardModel::addTriangle(GLuint inA, GLuint inB, GLuint inC)
{
    *mMiddleIndex++ = inA;
    *mMiddleIndex++ = inB;
    *mMiddleIndex++ = inC;
}

void CardModel::addTriangles(GLuint inA, GLuint inB, GLuint inC)
{
    *mTopIndex++ = inA;
    *mTopIndex++ = inB;
    *mTopIndex++ = inC;

    *mBottomIndex++ = inC + 1;
    *mBottomIndex++ = inB + 1;
    *mBottomIndex++ = inA + 1;
}

void CardModel::addQuad(GLuint inA, GLuint inB, GLuint inC, GLuint inD)
{
    addTriangle(inA, inB, inC);
    addTriangle(inA, inC, inD);
}

void CardModel::addQuads(GLuint inA, GLuint inB, GLuint inC, GLuint inD)
{
    addTriangles(inA, inB, inC);
    addTriangles(inA, inC, inD);
}

void CardModel::assembleDetailed()
{
    if (mDetail < 1) mDetail = 1;

    float w = mWidth / 2.0f;
    float h = mHeight / 2.0f;

    size_t numVertices = 8 * mDetail + 16;
    mVertices = new GLfloat[numVertices * 3];
    mTextureCoordinates = new GLfloat[numVertices * 2];

    mVertex = mVertices;
    mTextureCoordinate = mTextureCoordinates;

    // upper left corner
    GLfloat* previousVertex = mVertices;
    GLfloat* previousTexture = mTextureCoordinates;
    addVertex(mCornerRadius - w, h - mCornerRadius, mCornerRadius / mWidth,
        mCornerRadius / mHeight);
    addVertex(-w, h - mCornerRadius, 0.0f, mCornerRadius / mHeight);

    float theta = 90.0f / float(mDetail);
    for (int i = 1; i < mDetail; ++i)
    {
        float radians = float(i) * theta * 3.1415926535898f / 180.0f;
        float dx = mCornerRadius * cos(radians);
        float dy = mCornerRadius * sin(radians);
        addVertex(mCornerRadius - w - dx, h - mCornerRadius + dy,
            (mCornerRadius - dx) / mWidth, (mCornerRadius - dy) / mHeight);
    }

    addVertex(mCornerRadius - w, h, mCornerRadius / mWidth, 0.0f);

    // upper right corner
    addVertex(-previousVertex[0], previousVertex[1],
        1.0f - previousTexture[0], previousTexture[1]);
    previousVertex = mVertex - 6;
    previousTexture = mTextureCoordinate - 4;
    GLfloat* mirror = mVertex - 12;
    GLfloat* mirrorTC = mTextureCoordinate - 8;

    for (int i = 0; i < mDetail + 1; ++i)
    {
        addVertex(-mirror[0], mirror[1], 1.0f - mirrorTC[0], mirrorTC[1]);
        mirror -= 6;
        mirrorTC -= 4;
    }

    // lower right corner
    addVertex(previousVertex[0], -previousVertex[1], previousTexture[0],
        1.0f - previousTexture[1]);
    previousVertex = mVertex - 6;
    previousTexture = mTextureCoordinate - 4;
    mirror = mVertex - 12;
    mirrorTC = mTextureCoordinate - 8;

    for (int i = 0; i < mDetail + 1; ++i)
    {
        addVertex(mirror[0], -mirror[1], mirrorTC[0], 1.0f - mirrorTC[1]);
        mirror -= 6;
        mirrorTC -= 4;
    }

    // lower left corner
    addVertex(-previousVertex[0], previousVertex[1], 1.0f - previousTexture[0],
        previousTexture[1]);
    previousVertex = mVertex - 6;
    previousTexture = mTextureCoordinate - 4;
    mirror = mVertex - 12;
    mirrorTC = mTextureCoordinate - 8;

    for (int i = 0; i < mDetail + 1; ++i)
    {
        addVertex(-mirror[0], mirror[1], 1.0f - mirrorTC[0], mirrorTC[1]);
        mirror -= 6;
        mirrorTC -= 4;
    }

    for (size_t i = 0; i < numVertices; ++i)
    {
        size_t index = i * 2 + 1;
        mTextureCoordinates[index] = 1.0f - mTextureCoordinates[index];
    }

    mVertexBuffer.loadData(mVertices, numVertices, 3);
    mTextureBuffer.loadData(mTextureCoordinates, numVertices, 2);

    delete [] mVertices;
    delete [] mTextureCoordinates;

    size_t numTriangles = 16 * mDetail + 28;
    size_t numMiddleTriangles = 8 * mDetail + 8;
    size_t numTopTriangles = (numTriangles - numMiddleTriangles) / 2;

    mTopIndices = new GLuint[numTopTriangles * 3];
    mMiddleIndices = new GLuint[numMiddleTriangles * 3];
    mBottomIndices = new GLuint[numTopTriangles * 3];

    mTopIndex = mTopIndices;
    mMiddleIndex = mMiddleIndices;
    mBottomIndex = mBottomIndices;

    GLuint corners[5];
    int cornerSize = 2 * mDetail + 4;
    for (int i = 0; i < 5; ++i) corners[i] = cornerSize * i;

    // iterate through all four corners
    for (int i = 0; i < 4; ++i)
    {
        addQuads(corners[i], corners[i + 1] - 2, corners[(i + 1) % 4] + 2,
            corners[(i + 1) % 4]);
        addQuad(corners[i + 1] - 2, corners[i + 1] - 1, corners[(i + 1) % 4] + 3,
            corners[(i + 1) % 4] + 2);

        for (int j = 0; j < mDetail; ++j)
        {
            int k = 2 * (j + 1);
            addTriangles(corners[i], corners[i] + k, corners[i] + k + 2);
            addQuad(corners[i] + k, corners[i] + k + 1, corners[i] + k + 3,
                corners[i] + k + 2);
        }
    }

    addQuads(corners[0], corners[1], corners[2], corners[3]);

    mTopIndexBuffer.loadData(mTopIndices, numTopTriangles, 3);
    mMiddleIndexBuffer.loadData(mMiddleIndices, numMiddleTriangles, 3);
    mBottomIndexBuffer.loadData(mBottomIndices, numTopTriangles, 3);

    delete [] mTopIndices;
    delete [] mMiddleIndices;
    delete [] mBottomIndices;
}

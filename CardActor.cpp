#include "CardActor.hpp"
#include <QDebug>

CardActor::CardActor(CardModel& inCardModel, GLuint inFrontTexture,
    GLuint inBackTexture)
    : mCardModel(inCardModel), mFrontTexture(inFrontTexture),
      mBackTexture(inBackTexture), mRotation(0.0f), mFlip(0.0f)
{
}

CardActor::~CardActor()
{
}

void CardActor::draw()
{
    glColor3fv(mHighlight);
    mCardModel.drawEdge();

    if (mDrawFront)
        mCardModel.drawFront(mFrontTexture);
    else
        mCardModel.drawBack(mBackTexture);
}

bool CardActor::contains(float inX, float inY)
{
    float w = mCardModel.width() / 2.0f;
    float h = mCardModel.height() / 2.0f;

    return inX > mPosition[0] - w
        && inX < mPosition[0] + w
        && inY > mPosition[1] - h
        && inY < mPosition[1] + h;
}

void CardActor::willUpdate()
{
    //localMatrix().loadIdentity();
    //localMatrix().translate(mPosition[0], mPosition[1], mPosition[2]);
}

void CardActor::didUpdate()
{
    vec4f origin;
    origin[3] = 1.0f;

    modelMatrix().transform(origin, mModelOrigin);
    modelViewMatrix().transform(origin, mModelViewOrigin);

    origin[2] = 1.0f;
    modelViewMatrix().transform(origin, mDirection);

    mDirection[0] -= mModelViewOrigin[0];
    mDirection[1] -= mModelViewOrigin[1];
    mDirection[2] -= mModelViewOrigin[2];

    vec4f cameraToPolygon = mModelViewOrigin;
    CGE::normalize3(cameraToPolygon.getData());

    float dotProduct = CGE::dot(cameraToPolygon.getData(),
        mDirection.getData());

    mDrawFront = dotProduct < 0.0f;

    mPosition = mModelOrigin;
}

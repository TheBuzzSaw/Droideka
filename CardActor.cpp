#include "CardActor.hpp"
#include <QDebug>

CardActor::CardActor(CardModel& inCardModel, GLuint inFrontTexture,
    GLuint inBackTexture)
    : mCardModel(inCardModel), mFrontTexture(inFrontTexture),
      mBackTexture(inBackTexture)
{
}

CardActor::~CardActor()
{
}

void CardActor::draw()
{
    mCardModel.drawEdge();

    if (mDrawFront)
        mCardModel.drawFront(mFrontTexture);
    else
        mCardModel.drawBack(mBackTexture);
}

void CardActor::willUpdate()
{
    localMatrix().loadIdentity();
    localMatrix().translate(mPosition[0], mPosition[1], mPosition[2]);
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

    mDrawFront = mDirection[2] > 0.0f;
}

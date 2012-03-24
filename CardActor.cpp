#include "CardActor.hpp"
#include <QDebug>

CardActor::CardActor(CardModel& inCardModel, GLuint inFrontTexture,
    GLuint inBackTexture)
    : mCardModel(inCardModel), mFrontTexture(inFrontTexture),
      mBackTexture(inBackTexture), mRotation(0.0f), mFlip(0.0f),
      mIsHorizontal(false), mRotationStepsLeft(0), mFlipStepsLeft(0)
{
    setThickness(1.0f);
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

    if (mIsHorizontal)
    {
        float temp = w;
        w = h;
        h = temp;
    }

    return inX > mPosition[0] - w
        && inX < mPosition[0] + w
        && inY > mPosition[1] - h
        && inY < mPosition[1] + h;
}

void CardActor::rotate90()
{
    mIsHorizontal = !mIsHorizontal;
    mRotationStepsLeft += 4;
}

void CardActor::flip180()
{
    mFlipStepsLeft += 8;
}

void CardActor::setThickness(float inThickness)
{
    mThickness = inThickness;

    if (mThickness < 1.0f) mThickness = 1.0f;

    mOffsetBase = mThickness * mCardModel.depth() / 2.0f;
    mPosition[2] = mOffsetBase;
}

void CardActor::willUpdate()
{
    if (mRotationStepsLeft > 0)
    {
        mRotation -= 22.5f;

        if (mRotation < -180.0f)
            mRotation += 360.0f;

        --mRotationStepsLeft;
    }

    if (mFlipStepsLeft > 0)
    {
        mFlip += 22.5f;

        if (mFlip > 180.0f)
            mFlip -= 360.0f;

        float radians = mFlip * 3.1415926535898f / 180.0f;
        mPosition[2] = mOffsetBase + abs(sin(radians) * mCardModel.width() / 2.0f);

        --mFlipStepsLeft;
    }

    localMatrix().loadIdentity();
    localMatrix().translate(mPosition[0], mPosition[1], mPosition[2]);
    localMatrix().rotateZ(mRotation);
    localMatrix().rotateY(mFlip);
    localMatrix().scaleZ(mThickness);
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

    //mPosition = mModelOrigin;
}

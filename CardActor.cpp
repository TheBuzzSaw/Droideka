#include "CardActor.hpp"
#include <QDebug>

CardActor::CardActor(CardModel& inCardModel, GLuint inFrontTexture,
    GLuint inBackTexture)
    : mCardModel(inCardModel), mFrontTexture(inFrontTexture),
      mBackTexture(inBackTexture), mRotation(0.0f), mFlip(0.0f),
      mRotationStepsLeft(0), mFlipStepsLeft(0)
{
    mLineage = this;
    mParent = 0;
    mChild = 0;

    mUnderneath = 0.0f;
    mRadiusX = mCardModel.width() / 2.0f;
    mRadiusY = mCardModel.height() / 2.0f;
    mRadiusZ = mCardModel.depth() / 2.0f;

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

void CardActor::update()
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
        float opposite = abs(sin(radians) * mCardModel.width() / 2.0f);
        float sum = mRadiusZ + opposite;
        mOccupyZ = sum * 2;
        mPosition[2] = sum;

        updateUnderneath();

        --mFlipStepsLeft;
    }
}

void CardActor::confirmParent()
{
    if (mParent && !overlaps(*mParent))
    {
        mParent->mChild = 0;
        mParent = 0;
        mUnderneath = 0.0f;
        setLineage(this);
    }
}

void CardActor::setChild(CardActor* inCardActor)
{
    if (!mChild && inCardActor && inCardActor != this && !inCardActor->mParent)
    {
        mChild = inCardActor;
        mChild->mParent = this;
        mChild->setLineage(mLineage);
        updateUnderneath();
    }
}

bool CardActor::contains(float inX, float inY)
{
    return inX > mPosition[0] - mRadiusX
        && inX < mPosition[0] + mRadiusX
        && inY > mPosition[1] - mRadiusY
        && inY < mPosition[1] + mRadiusY;
}

bool CardActor::overlaps(const CardActor& inCardActor)
{
    return isInRange(x(), mRadiusX, inCardActor.x(), inCardActor.mRadiusX)
        && isInRange(y(), mRadiusY, inCardActor.y(), inCardActor.mRadiusY);
}

void CardActor::rotate90()
{
    float temp = mRadiusX;
    mRadiusX = mRadiusY;
    mRadiusY = temp;

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

    mRadiusZ = mThickness * mCardModel.depth() / 2.0f;
    mPosition[2] = mRadiusZ;
    mOccupyZ = mRadiusZ * 2.0f;
    updateUnderneath();
}

void CardActor::setPosition(float inX, float inY)
{
    float deltaX = inX - mPosition[0];
    float deltaY = inY - mPosition[1];
    move(deltaX, deltaY);
}

void CardActor::move(float inDeltaX, float inDeltaY)
{
    mPosition[0] += inDeltaX;
    mPosition[1] += inDeltaY;

    if (mChild) mChild->move(inDeltaX, inDeltaY);
}

void CardActor::willUpdate()
{
    localMatrix().loadIdentity();
    localMatrix().translate(mPosition[0], mPosition[1],
        mUnderneath + mPosition[2]);
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
}

void CardActor::updateUnderneath()
{
    updateUnderneath(mUnderneath);
}

void CardActor::updateUnderneath(float inPreviousUnderneath)
{
    mUnderneath = inPreviousUnderneath;

    if (mChild) mChild->updateUnderneath(mUnderneath + mOccupyZ);
}

void CardActor::setLineage(CardActor *inLineage)
{
    for (CardActor* i = this; i; i = i->mChild)
        i->mLineage = inLineage;
}

bool CardActor::isInRange(float inPointA, float inRadiusA, float inPointB,
    float inRadiusB)
{
    bool outResult;

    if (inPointA < inPointB)
    {
        outResult = inPointA + inRadiusA > inPointB - inRadiusB;
    }
    else
    {
        outResult = inPointB + inRadiusB > inPointA - inRadiusA;
    }

    return outResult;
}

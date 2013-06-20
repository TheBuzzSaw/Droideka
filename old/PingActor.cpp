#include "PingActor.hpp"

PingActor::PingActor(PingModel &inPingModel, float inX, float inY, float inRed,
    float inGreen, float inBlue) : mPingModel(inPingModel)
{
    mX = inX;
    mY = inY;
    mRed = inRed;
    mGreen = inGreen;
    mBlue = inBlue;
    mStepsRemaining = 40;
}

PingActor::~PingActor()
{

}

void PingActor::draw()
{
    mPingModel.draw(mRed, mGreen, mBlue);
}

void PingActor::willUpdate()
{
    if (mStepsRemaining > 0)
    {
        localMatrix().loadIdentity();
        localMatrix().translate(mX, mY, 0.0f);
        localMatrix().scale(float(mStepsRemaining * 2));

        --mStepsRemaining;
    }
}

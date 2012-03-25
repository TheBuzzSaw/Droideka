#ifndef PINGACTOR_HPP
#define PINGACTOR_HPP

#include "PingModel.hpp"
#include "Actor.hpp"

class PingActor : public Actor
{
public:
    PingActor(PingModel& inPingModel, float inX, float inY, float inRed,
        float inGreen, float inBlue);
    virtual ~PingActor();

    virtual void draw();

protected:
    virtual void willUpdate();

private:
    PingModel& mPingModel;
    float mX;
    float mY;
    float mRed;
    float mGreen;
    float mBlue;
    size_t mStepsRemaining;
};

#endif

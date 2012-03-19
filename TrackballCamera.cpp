#include "TrackballCamera.hpp"

TrackballCamera::TrackballCamera()
    : mDistance(0.0f), mRotation(0.0f), mAngle(0.0f)
{
}

TrackballCamera::~TrackballCamera()
{
}

void TrackballCamera::update()
{
    mViewMatrix.loadIdentity();
    if (mDistance > 0.0f) mViewMatrix.translate(0.0f, 0.0f, -mDistance);
    mViewMatrix.rotateX(mAngle);
    mViewMatrix.rotateZ(mRotation);
}

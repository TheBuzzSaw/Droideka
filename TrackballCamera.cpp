#include "TrackballCamera.hpp"

static const float MinimumDistance = 1.0f;

TrackballCamera::TrackballCamera()
    : mDistance(10.0f), mRotation(0.0f), mAngle(0.0f)
{
}

TrackballCamera::~TrackballCamera()
{
}

void TrackballCamera::update()
{
    mMatrix.loadIdentity();
    if (mDistance > 0.0f) mMatrix.translate(0.0f, 0.0f, -mDistance);
    mMatrix.rotateX(mAngle);
    mMatrix.rotateZ(mRotation);
    mMatrix.translate(-mPosition[0], -mPosition[1], -mPosition[2]);
}

void TrackballCamera::setPosition(const vec3f& inPosition)
{
    mPosition = inPosition;
}

void TrackballCamera::changePosition(const vec3f& inDelta)
{
    mPosition[0] += inDelta[0];
    mPosition[1] += inDelta[1];
    mPosition[2] += inDelta[2];
}

void TrackballCamera::setDistance(float inDistance)
{
    mDistance = inDistance < MinimumDistance ? MinimumDistance : inDistance;
}

void TrackballCamera::changeDistance(float inDelta)
{
    setDistance(mDistance + inDelta);
}

void TrackballCamera::setRotation(float inRotation)
{
    mRotation = inRotation;
}

void TrackballCamera::changeRotation(float inDelta)
{
    mRotation += inDelta;

    if (mRotation > 180.0f)
        mRotation -= 360.0f;
    else if (mRotation < -180.0f)
        mRotation += 360.0f;
}

void TrackballCamera::setAngle(float inAngle)
{
    mAngle = inAngle;
}

void TrackballCamera::changeAngle(float inDelta)
{
    mAngle += inDelta;
}

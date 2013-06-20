#ifndef TRACKBALLCAMERA_HPP
#define TRACKBALLCAMERA_HPP

#include "Vectors.hpp"
#include "Matrix4x4.hpp"

class TrackballCamera
{
public:
    TrackballCamera();
    ~TrackballCamera();

    inline const mat4f& matrix() const { return mMatrix; }

    void update();

    void smartPan(float inX, float inY);

    void setPosition(const vec3f& inPosition);
    void changePosition(const vec3f& inDelta);

    void setDistance(float inDistance);
    void changeDistance(float inDelta);

    void setRotation(float inRotation);
    void changeRotation(float inDelta);

    void setAngle(float inAngle);
    void changeAngle(float inDelta);

private:
    mat4f mMatrix;

    vec3f mPosition;
    float mDistance;
    float mRotation;
    float mAngle;
};

#endif

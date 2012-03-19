#ifndef TRACKBALLCAMERA_HPP
#define TRACKBALLCAMERA_HPP

#include "Vectors.hpp"
#include "Matrix4x4.hpp"

class TrackballCamera
{
public:
    TrackballCamera();
    ~TrackballCamera();

    inline const mat4f& matrix() const { return mViewMatrix; }

    void update();

private:
    mat4f mViewMatrix;
    float mDistance;
    float mRotation;
    float mAngle;
};

#endif

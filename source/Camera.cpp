#include "Camera.hpp"
#include <cmath>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::update()
{
    _matrix.setToIdentity();
    _matrix.translate(0.0f, 0.0f, -_distance);
    _matrix.rotate(_angle.toDegrees(), 1.0f, 0.0f, 0.0f);
    _matrix.rotate(_rotation.toDegrees(), 0.0f, 0.0f, 1.0f);
    _matrix.translate(-_position);
}

void Camera::panRelative(float x, float y)
{
    float theta = _rotation.toRadians();
    float c = cos(theta);
    float s = sin(theta);

    float deltaX = c * x;
    float deltaY = -s * x;
    deltaX += s * y;
    deltaY += c * y;

    _position.setX(_position.x() + deltaX);
    _position.setY(_position.y() + deltaY);
}

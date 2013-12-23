#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Rotation.hpp"
#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();
    ~Camera();

    void update();
    inline const QMatrix4x4& matrix() const { return _matrix; }

    inline const QVector3D& position() const { return _position; }
    inline void position(const QVector3D& p) { _position = p; }
    inline void adjustPosition(const QVector3D& p) { _position += p; }
    void panRelative(float x, float y);

    inline float distance() const { return _distance; }
    inline void distance(float d) { _distance = d > 0.0f ? d : 0.0f; }
    inline void adjustDistance(float d) { distance(_distance + d); }

    inline const RotationF rotation() const { return _rotation; }
    inline void rotation(const RotationF r) { _rotation = r; }
    inline void adjustRotation(const RotationF r) { _rotation += r; }

    inline const RotationF angle() const { return _angle; }
    inline void angle(const RotationF a) { _angle = a; }
    inline void adjustAngle(const RotationF a) { _angle += a; }

private:
    QMatrix4x4 _matrix;
    QVector3D _position;
    float _distance;
    RotationF _rotation;
    RotationF _angle;
};

#endif

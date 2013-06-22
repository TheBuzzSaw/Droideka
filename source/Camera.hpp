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
    void panRelative(float x, float y);

    inline float distance() const { return _distance; }
    inline void distance(float d) { _distance = d; }

    inline const Rotation rotation() const { return _rotation; }
    inline void rotation(const Rotation r) { _rotation = r; }
    inline void adjustRotation(const Rotation r) { _rotation += r; }

    inline const Rotation angle() const { return _angle; }
    inline void angle(const Rotation a) { _angle = a; }
    inline void adjustAngle(const Rotation a) { _angle += a; }

private:
    QMatrix4x4 _matrix;
    QVector3D _position;
    float _distance;
    Rotation _rotation;
    Rotation _angle;
};

#endif

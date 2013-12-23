#include "Rotation.hpp"

static inline float cycle(float radians)
{
    if (radians >= pi<float>())
        radians -= tau<float>();
    else if (radians < -pi<float>())
        radians += tau<float>();

    return radians;
}

const Rotation Rotation::fromDegrees(float degrees)
{
    return Rotation(qDegreesToRadians(degrees));
}

const Rotation Rotation::fromRadians(float radians)
{
    return Rotation(radians);
}

const Rotation Rotation::half()
{
    return Rotation(-pi<float>());
}

Rotation::Rotation() : _radians(0.0f)
{
}

Rotation::Rotation(float radians) : _radians(radians)
{
}

Rotation::Rotation(const Rotation &other) : _radians(other._radians)
{
}

Rotation::~Rotation()
{
}

Rotation& Rotation::operator=(const Rotation& other)
{
    _radians = other._radians;
    return *this;
}

Rotation& Rotation::operator+=(const Rotation& other)
{
    _radians = cycle(_radians + other._radians);
    return *this;
}

Rotation& Rotation::operator-=(const Rotation& other)
{
    _radians = cycle(_radians - other._radians);
    return *this;
}

const Rotation Rotation::operator+(const Rotation& other) const
{
    return Rotation(_radians) += other;
}

const Rotation Rotation::operator-(const Rotation& other) const
{
    return Rotation(_radians) -= other;
}

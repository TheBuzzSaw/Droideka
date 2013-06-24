#include "Rotation.hpp"
#include <cmath>

const Rotation Rotation::fromDegrees(float degrees)
{
    return fromRadians(degrees * RadiansPerDegree);
}

const Rotation Rotation::fromRadians(float radians)
{
    float result = 0.0f;

    if (radians > Pi)
        result = fmod(radians + Pi, TwoPi) - Pi;
    else if (radians < -Pi)
        result = fmod(radians - Pi, TwoPi) + Pi;
    else if (radians == radians)
        result = radians;

    return Rotation(result);
}

const Rotation Rotation::half()
{
    return Rotation(Pi);
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
    _radians += other._radians;

    if (_radians > Pi)
        _radians -= TwoPi;
    else if (_radians < -Pi)
        _radians += TwoPi;

    return *this;
}

Rotation& Rotation::operator-=(const Rotation& other)
{
    _radians -= other._radians;

    if (_radians > Pi)
        _radians -= TwoPi;
    else if (_radians < -Pi)
        _radians += TwoPi;

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

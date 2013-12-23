#ifndef ROTATION_HPP
#define ROTATION_HPP

#include <QtMath>

template<typename T>
constexpr T pi() { return 3.1415926535897932384626433832795028841971; }

template<typename T>
constexpr T halfPi() { return pi<T>() / T(2); }

template<typename T>
constexpr T tau() { return pi<T>() * T(2); }

class Rotation
{
public:
    static const Rotation fromDegrees(float degrees);
    static const Rotation fromRadians(float radians);
    static const Rotation half();

    Rotation();
    Rotation(const Rotation& other);
    ~Rotation();

    Rotation& operator=(const Rotation& other);
    Rotation& operator+=(const Rotation& other);
    Rotation& operator-=(const Rotation& other);

    const Rotation operator+(const Rotation& other) const;
    const Rotation operator-(const Rotation& other) const;

    inline float toRadians() const { return _radians; }
    inline float toDegrees() const { return qRadiansToDegrees(_radians); }

private:
    Rotation(float radians);

    float _radians;
};

#endif

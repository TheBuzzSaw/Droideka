#ifndef ROTATION_HPP
#define ROTATION_HPP

const float Pi = 3.1415926535898f;
const float TwoPi = Pi * 2.0f;
const float DegreesPerRadian = 180.0f / Pi;
const float RadiansPerDegree = Pi / 180.0f;

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
    inline float toDegrees() const { return _radians * DegreesPerRadian; }

private:
    Rotation(float radians);

    float _radians;
};

#endif

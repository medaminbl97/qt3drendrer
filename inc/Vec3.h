#pragma once
#include <cmath>

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float x_, float y_, float z_);
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(float scalar) const;
    Vec3 cross(const Vec3& other) const;
    float dot(const Vec3& other) const;
    float length() const;
    Vec3 normalized() const;
};

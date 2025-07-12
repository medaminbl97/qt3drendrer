#include <Vec3.h>


Vec3::~Vec3(){}
Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const
{
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::cross(const Vec3& other) const
{
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vec3::dot(const Vec3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

float Vec3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized() const
{
    float len = length();
    if (len == 0.0f) return Vec3(0, 0, 0);
    return (*this) * (1.0f / len);
}
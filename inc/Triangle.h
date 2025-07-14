#pragma once

#include "Vec3.h"

class Triangle
{
public:
    Vec3 v0;
    Vec3 v1;
    Vec3 v2;

    Triangle() = default;
    Triangle(const Vec3& a, const Vec3& b, const Vec3& c);
    Vec3 normal() const;
    bool isVisible() const;
};

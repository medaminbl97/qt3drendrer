#pragma once

#include "Vec3.h"

class Triangle
{
public:
    Vec3 v0;
    Vec3 v1;
    Vec3 v2;

    Triangle() = default;
    Triangle(const Vec3& a, const Vec3& b, const Vec3& c)
        : v0(a), v1(b), v2(c) {}

    Vec3 normal() const
    {
        Vec3 edge1 = v1 - v0;
        Vec3 edge2 = v2 - v0;
        return edge1.cross(edge2).normalized();
    }
    bool isVisible() const;
};

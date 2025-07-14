#pragma once

#include "Vec3.h"

class Polygon
{
public:
    Vec3 v0;
    Vec3 v1;
    Vec3 v2;
    Vec3 v3; // Used only if it's a quad

    bool isQuad;

    Polygon();
    Polygon(const Vec3& a, const Vec3& b, const Vec3& c);
    Polygon(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d);

    Vec3 normal() const;
    bool isVisible() const;
};

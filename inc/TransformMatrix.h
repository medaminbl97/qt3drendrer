#pragma once

#include "Triangle.h"
#include "Vec3.h"
#include <cmath>

class TransformMatrix
{
public:
    // Rotate a Vec3 around X axis
    static Vec3 rotateX(const Vec3& v, float angle)
    {
        float c = std::cos(angle);
        float s = std::sin(angle);
        return Vec3(
            v.x,
            v.y * c - v.z * s,
            v.y * s + v.z * c
        );
    }

    // Rotate a Vec3 around Y axis
    static Vec3 rotateY(const Vec3& v, float angle)
    {
        float c = std::cos(angle);
        float s = std::sin(angle);
        return Vec3(
            v.x * c + v.z * s,
            v.y,
            -v.x * s + v.z * c
        );
    }

    // Rotate a Vec3 around Z axis
    static Vec3 rotateZ(const Vec3& v, float angle)
    {
        float c = std::cos(angle);
        float s = std::sin(angle);
        return Vec3(
            v.x * c - v.y * s,
            v.x * s + v.y * c,
            v.z
        );
    }

    // Rotate an entire triangle around X axis
    static Triangle rotateTriangleX(const Triangle& tri, float angle)
    {
        return Triangle(
            rotateX(tri.v0, angle),
            rotateX(tri.v1, angle),
            rotateX(tri.v2, angle)
        );
    }

    // Rotate an entire triangle around Y axis
    static Triangle rotateTriangleY(const Triangle& tri, float angle)
    {
        return Triangle(
            rotateY(tri.v0, angle),
            rotateY(tri.v1, angle),
            rotateY(tri.v2, angle)
        );
    }

    // Rotate an entire triangle around Z axis
    static Triangle rotateTriangleZ(const Triangle& tri, float angle)
    {
        return Triangle(
            rotateZ(tri.v0, angle),
            rotateZ(tri.v1, angle),
            rotateZ(tri.v2, angle)
        );
    }

    static QPolygon projectTo2D(const Triangle& tri, const QPoint& origin)
        {
            QPoint p0(origin.x() + static_cast<int>(tri.v0.x),
                    origin.y() - static_cast<int>(tri.v0.y));
            QPoint p1(origin.x() + static_cast<int>(tri.v1.x),
                    origin.y() - static_cast<int>(tri.v1.y));
            QPoint p2(origin.x() + static_cast<int>(tri.v2.x),
                    origin.y() - static_cast<int>(tri.v2.y));

            QPolygon polygon;
            polygon << p0 << p1 << p2;
            return polygon;
        }
};

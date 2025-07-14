#pragma once

#include "Polygon.h"
#include "Vec3.h"
#include <cmath>
#include <QPolygon>
#include <QPoint>

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

    // Rotate an entire polygon around X axis
    static void rotatePolygonX(Polygon& poly, float angle)
    {
        if (poly.isQuad) {
            poly = Polygon(
                rotateX(poly.v0, angle),
                rotateX(poly.v1, angle),
                rotateX(poly.v2, angle),
                rotateX(poly.v3, angle)
            );
        } else {
            poly = Polygon(
                rotateX(poly.v0, angle),
                rotateX(poly.v1, angle),
                rotateX(poly.v2, angle)
            );
        }
    }

    // Rotate an entire polygon around Y axis
    static void rotatePolygonY(Polygon& poly, float angle)
    {
        if (poly.isQuad) {
            poly = Polygon(
                rotateY(poly.v0, angle),
                rotateY(poly.v1, angle),
                rotateY(poly.v2, angle),
                rotateY(poly.v3, angle)
            );
        } else {
            poly = Polygon(
                rotateY(poly.v0, angle),
                rotateY(poly.v1, angle),
                rotateY(poly.v2, angle)
            );
        }
    }

    // Rotate an entire polygon around Z axis
    static void rotatePolygonZ(Polygon& poly, float angle)
    {
        if (poly.isQuad) {
            poly = Polygon(
                rotateZ(poly.v0, angle),
                rotateZ(poly.v1, angle),
                rotateZ(poly.v2, angle),
                rotateZ(poly.v3, angle)
            );
        } else {
            poly = Polygon(
                rotateZ(poly.v0, angle),
                rotateZ(poly.v1, angle),
                rotateZ(poly.v2, angle)
            );
        }
    }

    // Project polygon to 2D (returns QPolygon)
    static QPolygon projectTo2D(const Polygon& poly, const QPoint& origin)
    {
        QPolygon qpoly;
        qpoly << QPoint(origin.x() + static_cast<int>(poly.v0.x),
                        origin.y() - static_cast<int>(poly.v0.y));
        qpoly << QPoint(origin.x() + static_cast<int>(poly.v1.x),
                        origin.y() - static_cast<int>(poly.v1.y));
        qpoly << QPoint(origin.x() + static_cast<int>(poly.v2.x),
                        origin.y() - static_cast<int>(poly.v2.y));

        if (poly.isQuad) {
            qpoly << QPoint(origin.x() + static_cast<int>(poly.v3.x),
                            origin.y() - static_cast<int>(poly.v3.y));
        }

        return qpoly;
    }
};

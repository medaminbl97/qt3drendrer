#include "Polygon.h"

Polygon::Polygon()
    : v0(), v1(), v2(), v3(), isQuad(false)
{
}

Polygon::Polygon(const Vec3& a, const Vec3& b, const Vec3& c)
    : v0(a), v1(b), v2(c), v3(), isQuad(false)
{
}

Polygon::Polygon(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d)
    : v0(a), v1(b), v2(c), v3(d), isQuad(true)
{
}

Vec3 Polygon::normal() const
{
    // For quad, use first triangle (v0, v1, v2) to compute normal
    Vec3 edge1 = v1 - v0;
    Vec3 edge2 = v2 - v0;
    return edge1.cross(edge2).normalized();
}

bool Polygon::isVisible() const
{
    Vec3 n = normal();
    Vec3 cameraDir(0.0f, 0.0f, -1.0f); // Looking into -Z

    float dotProd = n.dot(cameraDir);

    return dotProd >= 0.0f; // Visible if facing camera
}

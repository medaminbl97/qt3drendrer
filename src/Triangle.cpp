#include <Triangle.h>


Triangle::Triangle(const Vec3& a, const Vec3& b, const Vec3& c)
    : v0(a), v1(b), v2(c) {}

Vec3 Triangle::normal() const
{
    Vec3 edge1 = v1 - v0;
    Vec3 edge2 = v2 - v0;
    return edge1.cross(edge2).normalized();
}

bool Triangle::isVisible() const
{
    Vec3 n = normal();
    Vec3 cameraDir(0.0f, 0.0f, -1.0f); // Looking into -Z

    float dotProd = n.dot(cameraDir);

    return dotProd >= 0.0f; // Visible if angle < 90°
}

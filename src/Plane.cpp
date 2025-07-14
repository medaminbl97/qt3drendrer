#include "Plane.h"
#include "Vec3.h"
#include "Polygon.h"

Plane::Plane(const QString& name)
    : BaseModel(name)
{
    // Define default vertices (simple 1x1 plane centered at origin)
    Vec3 v0(0, 0, 0);
    Vec3 v1(100, 0, 0);
    Vec3 v2(0, 100, 0);
    Vec3 v3(100, 100, 0);

    // Polygon 1: v0, v1, v2
    Polygon t1(v0, v1, v2);
    // Polygon 2: v2, v1, v3
    Polygon t2(v2, v1, v3);

    // Add to base class vector
    mesh.push_back(t1);
    mesh.push_back(t2);
}

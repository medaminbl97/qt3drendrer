#include "Plane.h"
#include "Vec3.h"
#include "Triangle.h"

Plane::Plane(QGraphicsView* graphicsView)
    : BaseModel(graphicsView)
{
    // Define default vertices (simple 1x1 plane centered at origin)
    Vec3 v0(0, 0, 0);
    Vec3 v1(100, 0, 0);
    Vec3 v2(0, 100, 0);
    Vec3 v3(100, 100, 0);

    // Triangle 1: v0, v1, v2
    Triangle t1(v0, v1, v2);
    // Triangle 2: v2, v1, v3
    Triangle t2(v2, v1, v3);

    // Add to base class vector
    m_triangles.push_back(t1);
    m_triangles.push_back(t2);
}

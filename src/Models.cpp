#include "Models.h"
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
        for(auto& poly : mesh){
        poly.normalize(100.0f);
    }
}


// ---- CUBE ----

Cube::Cube(const QString& name)
    : BaseModel(name)
{
    // Vertices
    Vec3 v0(-0.5f, -0.5f, -0.5f);
    Vec3 v1(0.5f, -0.5f, -0.5f);
    Vec3 v2(0.5f, 0.5f, -0.5f);
    Vec3 v3(-0.5f, 0.5f, -0.5f);
    Vec3 v4(-0.5f, -0.5f, 0.5f);
    Vec3 v5(0.5f, -0.5f, 0.5f);
    Vec3 v6(0.5f, 0.5f, 0.5f);
    Vec3 v7(-0.5f, 0.5f, 0.5f);

    mesh.emplace_back(v4, v5, v6, v7); // Front
    mesh.emplace_back(v0, v1, v2, v3); // Back
    mesh.emplace_back(v0, v3, v7, v4); // Left
    mesh.emplace_back(v1, v2, v6, v5); // Right
    mesh.emplace_back(v3, v2, v6, v7); // Top
    mesh.emplace_back(v0, v1, v5, v4); // Bottom

    for(auto& poly : mesh){
        poly.normalize(0.5f);
    }
}

// ---- PYRAMID ----

Pyramid::Pyramid(const QString& name)
    : BaseModel(name)
{
    Vec3 v0(-0.5f, 0.0f, -0.5f);
    Vec3 v1(0.5f, 0.0f, -0.5f);
    Vec3 v2(0.5f, 0.0f, 0.5f);
    Vec3 v3(-0.5f, 0.0f, 0.5f);
    Vec3 v4(0.0f, 1.0f, 0.0f);

    mesh.emplace_back(v0, v1, v2, v3); // Base
    mesh.emplace_back(v0, v1, v4);     // Side 1
    mesh.emplace_back(v1, v2, v4);     // Side 2
    mesh.emplace_back(v2, v3, v4);     // Side 3
    mesh.emplace_back(v3, v0, v4);     // Side 4
        for(auto& poly : mesh){
        poly.normalize(0.5f);
    }
}

// ---- TORUS ----

Torus::Torus(const QString& name)
    : BaseModel(name)
{
    const float R = 1.0f;      // Main radius
    const float r = 0.3f;      // Tube radius
    const int nSides = 16;     // Tube divisions
    const int nRings = 24;     // Ring divisions

    for (int i = 0; i < nRings; ++i)
    {
        float u0 = (i / (float)nRings) * 2.0f * M_PI;
        float u1 = ((i + 1) / (float)nRings) * 2.0f * M_PI;

        for (int j = 0; j < nSides; ++j)
        {
            float v0 = (j / (float)nSides) * 2.0f * M_PI;
            float v1 = ((j + 1) / (float)nSides) * 2.0f * M_PI;

            // Four vertices of quad
            Vec3 p0(
                (R + r * cos(v0)) * cos(u0),
                (R + r * cos(v0)) * sin(u0),
                r * sin(v0)
            );

            Vec3 p1(
                (R + r * cos(v0)) * cos(u1),
                (R + r * cos(v0)) * sin(u1),
                r * sin(v0)
            );

            Vec3 p2(
                (R + r * cos(v1)) * cos(u1),
                (R + r * cos(v1)) * sin(u1),
                r * sin(v1)
            );

            Vec3 p3(
                (R + r * cos(v1)) * cos(u0),
                (R + r * cos(v1)) * sin(u0),
                r * sin(v1)
            );

            mesh.emplace_back(p0, p1, p2, p3);
        }
    }

        for(auto& poly : mesh){
        poly.normalize(1.0f);
    }
}
#pragma once

#include <vector>
#include <string>
#include "Vec3.h"
#include "Polygon.h"

class ObjLoader
{
private:
    std::vector<Vec3> vertices;
    std::vector<Polygon> mesh;

public:
    ObjLoader() = default;

    bool loadFile(const std::string& path);
    const std::vector<Polygon>& getMesh() const;
};

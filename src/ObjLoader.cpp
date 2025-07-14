#include "ObjLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool ObjLoader::loadFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return false;
    }

    vertices.clear();
    mesh.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        } else if (prefix == "f") {
            std::vector<int> indices;
            std::string vertStr;

            while (iss >> vertStr) {
                std::istringstream viss(vertStr);
                std::string vIdxStr;
                std::getline(viss, vIdxStr, '/');
                int vIdx = std::stoi(vIdxStr);
                indices.push_back(vIdx - 1); // OBJ indices start at 1
            }

            if (indices.size() == 3) {
                mesh.emplace_back(
                    vertices[indices[0]],
                    vertices[indices[1]],
                    vertices[indices[2]]
                );
            } else if (indices.size() == 4) {
                mesh.emplace_back(
                    vertices[indices[0]],
                    vertices[indices[1]],
                    vertices[indices[2]],
                    vertices[indices[3]]
                );
            } else {
                std::cerr << "Unsupported face with " << indices.size() << " vertices. Only triangles and quads are supported.\n";
            }
        }
    }

    file.close();
    return true;
}


const std::vector<Polygon>& ObjLoader::getMesh() const
{
    return mesh;
}

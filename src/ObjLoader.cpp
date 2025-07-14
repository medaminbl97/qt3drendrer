#include "ObjLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

ObjLoader::ObjLoader(std::vector<Polygon> *mesh) : mesh(mesh)
{
}

bool ObjLoader::loadFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return false;
    }

    vertices.clear();
    mesh->clear();
    float max = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            float current_max = std::abs(std::max(x, std::max(y, z)));
            max = current_max > max ? current_max : max;

            vertices.emplace_back(x, y, z);
        } else if (prefix == "f") {
            std::vector<int> indices;
            std::string vertStr;

            while (iss >> vertStr) {
                std::istringstream viss(vertStr);
                std::string vIdxStr;
                std::getline(viss, vIdxStr, '/');
                if (vIdxStr == "#"){
                    break;
                }
                int vIdx = std::stoi(vIdxStr);
                indices.push_back(vIdx - 1); // OBJ indices start at 1
            }

            if (indices.size() == 3) {
                mesh->emplace_back(
                    vertices[indices[0]],
                    vertices[indices[1]],
                    vertices[indices[2]]
                );
            } else if (indices.size() == 4) {
                mesh->emplace_back(
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

    for(auto& poly : *mesh){
        poly.normalize(max);
    }

    file.close();
    return true;
}



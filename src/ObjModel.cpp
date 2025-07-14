#include "ObjModel.h"
#include "Vec3.h"
#include "Polygon.h"
#include "ObjLoader.h"

ObjModel::ObjModel(const QString& name, const std::string& path)
    : BaseModel(name)
{
    ObjLoader loader(&mesh);
    loader.loadFile(path);
}

#pragma once

#include "BaseModel.h"

class ObjModel : public BaseModel
{
public:
    ObjModel(const QString& name, const std::string& path);
    ~ObjModel() override = default;
};

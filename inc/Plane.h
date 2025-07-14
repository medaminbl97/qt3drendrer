#pragma once

#include "BaseModel.h"

class Plane : public BaseModel
{
public:
    Plane(const QString& name);
    ~Plane() override = default;
};

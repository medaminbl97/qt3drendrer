#pragma once

#include "BaseModel.h"

class Plane : public BaseModel
{
public:
    Plane(const QString& name);
    ~Plane() override = default;
};

class Cube : public BaseModel
{
public:
    Cube(const QString& name);
    ~Cube() override = default;
};

class Cone : public BaseModel
{
public:
    Cone(const QString& name);
    ~Cone() override = default;
};

class Torus : public BaseModel
{
public:
    Torus(const QString& name);
    ~Torus() override = default;
};

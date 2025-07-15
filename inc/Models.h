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

class Pyramid : public BaseModel
{
public:
    Pyramid(const QString& name);
    ~Pyramid() override = default;
};

class Torus : public BaseModel
{
public:
    Torus(const QString& name);
    ~Torus() override = default;
};

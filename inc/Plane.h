#pragma once


#include "BaseModel.h"

class Plane : public BaseModel
{
public:
    Plane(QGraphicsView* graphicsView);
    ~Plane() override = default;
};

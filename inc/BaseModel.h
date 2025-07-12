#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QPoint>
#include "Triangle.h"
#include "TransformMatrix.h"

class BaseModel
{
private:
    QTimer m_timer;
    TransformMatrix m_tmatrix;
    std::vector<Triangle> m_triangles;
    QGraphicsView * graphicsView;
public:
    BaseModel(QGraphicsView * graphicsView);
    virtual ~BaseModel() = 0;
    virtual void draw() const;
    virtual void rotateX(float angle) const;
    virtual void rotateY(float angle) const;
    virtual void rotateZ(float angle) const;
    virtual void rotateZ(float angle) const;
private:
    QPoint getOrigin() const;
};


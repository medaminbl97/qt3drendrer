#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QPoint>
#include "Triangle.h"
#include "TransformMatrix.h"
#include "ModelView.h"

class BaseModel
{
public:
    QString m_name;
protected:
    QTimer m_timer;
    std::vector<Triangle> m_triangles;
    ModelView * m_modelview;
    bool m_tabOpened;
public:
    BaseModel(const QString& name = "no_name");
    void loadModelFromOBJ(const std::string& path);
    ModelView * getTab();
    bool isTabOpened() const;
    void setTabOpened(bool value);
    virtual ~BaseModel() = 0;
    virtual void draw() const;
    virtual void rotateX(float angle) const;
    virtual void rotateY(float angle) const;
    virtual void rotateZ(float angle) const;

private:
    QPoint getOrigin() const;
};


#include "BaseModel.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <QVBoxLayout>



BaseModel::BaseModel(const QString& name) :  m_name(name), m_tabOpened(false)
{   
}

void BaseModel::setTabOpened(bool value)
{
    m_tabOpened = value;
}

bool BaseModel::isTabOpened() const
{
    return m_tabOpened;
}

BaseModel::~BaseModel() = default;

void BaseModel::draw() const
{
    m_modelview->draw(mesh);
}

void BaseModel::rotateX(float angle)
{
    qDebug() << "Rotating around X axis!";
    for (auto& poly : mesh)
    {
        TransformMatrix::rotatePolygonX(poly,angle);
    }
}
void BaseModel::rotateY(float angle)
{
    qDebug() << "Rotating around Y axis!";
        for (auto& poly : mesh)
    {
        TransformMatrix::rotatePolygonY(poly,angle);
    }
}

void BaseModel::rotateZ(float angle)
{
    qDebug() << "Rotating around Z axis!";
    for (auto& poly : mesh)
    {
        TransformMatrix::rotatePolygonZ(poly,angle);
    }
}



void BaseModel::loadModelFromOBJ(const std::string& path)
{
    // Parse .obj
    // Compute bounding box (minX, maxX, minY, maxY, minZ, maxZ)
    // Find largest dimension (e.g., max(maxX - minX, maxY - minY, maxZ - minZ))
    // Compute scale factor to make largest dimension = 100
    // Apply scaling and offset so center is at (0, 0, 0)
    // Store mesh in m_trangles

    // Example placeholder logic
    // for each vertex v:
    // v.x = (v.x - centerX) * scale
    // v.y = (v.y - centerY) * scale
    // v.z = (v.z - centerZ) * scale
}

ModelView *BaseModel::getTab()
{   
    m_modelview = new ModelView();
    m_modelview->setObjectName("Model Tab");
    return m_modelview;
}

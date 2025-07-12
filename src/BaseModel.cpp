#include "BaseModel.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QtMath>

BaseModel::BaseModel(QGraphicsView* graphicsView)
    : graphicsView(graphicsView)
{
}

BaseModel::~BaseModel() = default;

void BaseModel::draw() const
{
    qDebug() << "Drawing triangles!";

    if (!graphicsView) {
        qWarning() << "Graphics view is null!";
        return;
    }

    QPixmap pixmap(graphicsView->size());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::NoBrush);

    QPoint origin = getOrigin();

    for (const auto& tri : m_triangles)
    {
        if (!tri.isVisible())
            continue;
        QPolygon polygon = m_tmatrix.projectTo2D(tri, origin);
        painter.drawPolygon(polygon);
    }

    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(pixmap);
    graphicsView->setScene(scene);
}

void BaseModel::rotateX(float angle) const
{
    qDebug() << "Rotating around X axis!";
    for (auto& tri : m_triangles)
    {
        m_tmatrix.rotateTriangleX(tri,angle);
    }
}
void BaseModel::rotateY(float angle) const
{
    qDebug() << "Rotating around Y axis!";
        for (auto& tri : m_triangles)
    {
        m_tmatrix.rotateTriangleY(tri,angle);
    }
}

void BaseModel::rotateZ(float angle) const
{
    qDebug() << "Rotating around Z axis!";
    for (auto& tri : m_triangles)
    {
        m_tmatrix.rotateTriangleZ(tri,angle);
    }
}

QPoint BaseModel::getOrigin() const
{
    // Center of graphics view
    int centerX = graphicsView->width() / 2;
    int centerY = graphicsView->height() / 2;
    return QPoint(centerX, centerY);
}

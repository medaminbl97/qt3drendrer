#include "ModelView.h"
#include "ui_modelview.h"
#include <QPainter>

ModelView::ModelView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModelView)
{
    ui->setupUi(this);
    setUpToolBtns();
}

void ModelView::setUpToolBtns(){
    QIcon rx_icon(":/icons/rx.png"); 
    QIcon ry_icon(":/icons/ry.png"); 
    QIcon rz_icon(":/icons/rz.png"); 
    ui->rxBtn->setIcon(rx_icon);
    ui->ryBtn->setIcon(ry_icon);
    ui->rzBtn->setIcon(rz_icon);
}


void ModelView::draw(const std::vector<Triangle>& triangles) const
{
    qDebug() << "Drawing triangles!";
    if (!ui->graphicsView) {
        qWarning() << "Graphics view is null!";
        return;
    }

    QPixmap pixmap(ui->graphicsView->size());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::NoBrush);

    QPoint origin = getOrigin();

    for (const auto& tri : triangles)
    {
        // if (!tri.isVisible())
        //     continue;
        QPolygon polygon = TransformMatrix::projectTo2D(tri, origin);
        painter.drawPolygon(polygon);
    }

    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
}

QPoint ModelView::getOrigin() const
{
    // Center of graphics view
    int centerX = ui->graphicsView->width() / 2;
    int centerY = ui->graphicsView->height() / 2;
    return QPoint(centerX, centerY);
}


ModelView::~ModelView()
{
    delete ui;
}



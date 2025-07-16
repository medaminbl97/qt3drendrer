#include "ModelView.h"
#include "ui_modelview.h"
#include <QPainter>
#include <QColorDialog>
#include <QPushButton>
#include <iostream>

ModelView::ModelView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModelView), m_tabActive(false)
    , m_color(82, 75, 204),
    rotatex(false),
    rotatey(false),
    rotatez(false)

{
    ui->setupUi(this);
    setUpToolBtns();
    m_gizmo.x = Vec3(1, 0, 0);
    m_gizmo.y = Vec3(0, 1, 0);
    m_gizmo.z = Vec3(0, 0, 1);

}

void ModelView::setUpToolBtns(){
    QIcon rx_icon(":/icons/rx.png"); 
    QIcon ry_icon(":/icons/ry.png"); 
    QIcon rz_icon(":/icons/rz.png"); 
    QIcon col_icon(":/icons/col.png"); 
    ui->rxBtn->setIcon(rx_icon);
    ui->ryBtn->setIcon(ry_icon);
    ui->rzBtn->setIcon(rz_icon);
    ui->colorBtn->setIcon(col_icon);
    connect(ui->colorBtn, &QPushButton::clicked, this, openColorDialog);
    connect(ui->rxBtn, &QPushButton::clicked, this, onRotatex);
    connect(ui->ryBtn, &QPushButton::clicked, this, onRotatey);
    connect(ui->rzBtn, &QPushButton::clicked, this, onRotatez);


}

void ModelView::onRotatex(){
    rotatex = !rotatex;
    ui->rxBtn->setChecked(rotatex);
}
void ModelView::onRotatey(){
    rotatey = !rotatey;
    ui->ryBtn->setChecked(rotatey);
}
void ModelView::onRotatez(){
    rotatez = !rotatez;
    ui->rzBtn->setChecked(rotatez);
}

void ModelView::openColorDialog()
{
    QColor chosenColor = QColorDialog::getColor(Qt::white, nullptr, "Select Color");

    if (chosenColor.isValid()) {
        m_color = chosenColor;
    }
}

void ModelView::rotateGizmo(const QString& axisLabel, float angle)
{

    if (axisLabel == "x" || axisLabel == "X")
    {
        
        m_gizmo.x = TransformMatrix::rotateX(m_gizmo.x, angle);
        m_gizmo.y = TransformMatrix::rotateX(m_gizmo.y, angle);
        m_gizmo.z = TransformMatrix::rotateX(m_gizmo.z, angle);
    }
    else if (axisLabel == "y" || axisLabel == "Y")
    {
        m_gizmo.x = TransformMatrix::rotateY(m_gizmo.x, angle);
        m_gizmo.y = TransformMatrix::rotateY(m_gizmo.y, angle);
        m_gizmo.z = TransformMatrix::rotateY(m_gizmo.z, angle);
    }
    else if (axisLabel == "z" || axisLabel == "Z")
    {
        m_gizmo.x = TransformMatrix::rotateZ(m_gizmo.x, angle);
        m_gizmo.y = TransformMatrix::rotateZ(m_gizmo.y, angle);
        m_gizmo.z = TransformMatrix::rotateZ(m_gizmo.z, angle);
    }
    else
        return; // Invalid axis, do nothing
}


void ModelView::drawGizmo(QPainter& painter)
{
    const int axisLength = 50;
    const int padding = 70;

    // Bottom-left corner
    QPoint corner(0, ui->graphicsView->height());
    QPoint origin(corner.x() + padding, corner.y() - padding);

    Vec3 xAxis = m_gizmo.x * axisLength;
    Vec3 yAxis = m_gizmo.y * axisLength;
    Vec3 zAxis = m_gizmo.z * axisLength;

    QPoint xEnd(origin.x() + static_cast<int>(xAxis.x), origin.y() - static_cast<int>(xAxis.y));
    QPoint yEnd(origin.x() + static_cast<int>(yAxis.x), origin.y() - static_cast<int>(yAxis.y));
    QPoint zEnd(origin.x() + static_cast<int>(zAxis.x), origin.y() - static_cast<int>(zAxis.y));

    painter.setPen(QPen(Qt::red, 2));
    painter.drawLine(origin, xEnd);
    painter.drawText(xEnd + QPoint(5, -5), "X");

    painter.setPen(QPen(Qt::green, 2));
    painter.drawLine(origin, yEnd);
    painter.drawText(yEnd + QPoint(5, -5), "Y");

    painter.setPen(QPen(Qt::blue, 2));
    painter.drawLine(origin, zEnd);
    painter.drawText(zEnd + QPoint(5, -5), "Z");
}

void printPolygonInfo(const Polygon& poly){
    qDebug() << "Polygon info : ";

    qDebug() << "  v0:" << poly.v0.x << poly.v0.y << poly.v0.z;
    qDebug() << "  v1:" << poly.v1.x << poly.v1.y << poly.v1.z;
    qDebug() << "  v2:" << poly.v2.x << poly.v2.y << poly.v2.z;
    
    if (poly.isQuad) {
        qDebug() << "  v3:" << poly.v3.x << poly.v3.y << poly.v3.z;
    }

    Vec3 n = poly.normal();
    qDebug() << "  Normal:" << n.x << n.y << n.z;
}

void ModelView::draw(const std::vector<Polygon>& mesh, const QString& model_name, const Vec3& light)
{
    // qDebug() << "Drawing mesh for!" + model_name;
    if (!ui->graphicsView) {
        qWarning() << "Graphics view is null!";
        return;
    }
    QPixmap pixmap(ui->graphicsView->size());
    pixmap.fill(Qt::transparent);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    drawGizmo(painter);
    painter.setPen(Qt::NoPen);
    // painter.setPen(Qt::black);
    
    QPoint origin = getOrigin();
    for (const auto& poly : mesh)
    {   
        //printPolygonInfo(poly);
        if (!poly.isVisible())
            continue;
        float diffuse = poly.normal().normalized().dot(light.normalized());
        qDebug() << "Intensity : " << diffuse;
        
        diffuse = std::max(0.0f, diffuse);

        // Calculate new RGB
        int r = static_cast<int>(m_color.red()   * diffuse);
        int g = static_cast<int>(m_color.green() * diffuse);
        int b = static_cast<int>(m_color.blue()  * diffuse);

        // You can also clamp min diffuse to avoid going completely black if desired
        // float minDiffuse = 0.2f;
        // diffuse = std::max(diffuse, minDiffuse);

        QColor shadedColor(r, g, b, m_color.alpha());

        // Use it in painter
        painter.setBrush(shadedColor);

        QPolygon polygon = TransformMatrix::projectTo2D(poly, origin);
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


bool ModelView::isActive() const{
    return m_tabActive;
}


void ModelView::showEvent(QShowEvent *event)
{
    m_tabActive = true;
}

void ModelView::hideEvent(QHideEvent *event)
{
    m_tabActive = false;

}

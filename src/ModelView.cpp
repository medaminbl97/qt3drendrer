#include "ModelView.h"
#include "ui_modelview.h"
#include <QPainter>

ModelView::ModelView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    connect(ui->addCircleBtn, &QPushButton::clicked,
        this, drawCircle);
}

ModelView::~ModelView()
{
    delete ui;
}

void ModelView::drawCircle()
{
    // Create pixmap
    qDebug() << "Drawing a circle !";
    QPixmap pixmap(ui->graphicsView->size());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::yellow);

    int centerX = ui->graphicsView->width() / 2;
    int centerY = ui->graphicsView->height() / 2;
    int radius = qMin(ui->graphicsView->width(), ui->graphicsView->height()) / 4;

    painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

    // Create scene
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);

    ui->graphicsView->setScene(scene);
}



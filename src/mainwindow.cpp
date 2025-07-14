#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "Plane.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
    m_modelviewtabs(new ModelViewTabs(this))
{
    ui->setupUi(this);
    connect(ui->addModelBtn, &QPushButton::clicked,this, onAddModelBtnClicked);
    
    QTreeWidgetItem *rootItem = new QTreeWidgetItem();
    QIcon icon(":/icons/3d-model.png");
    rootItem->setText(0, "Models");
    rootItem->setIcon(0, icon);
    ui->modelsTree->addTopLevelItem(rootItem);
    ui->modelsTree->setHeaderHidden(true);
    connect(ui->modelsTree, &QTreeWidget::itemClicked, this, &Widget::onModelItemClicked);

}


Widget::~Widget()
{
    delete m_modelsDialog;
    delete m_modelviewtabs;
    delete ui;
}

void Widget::onAddModelBtnClicked()
{   
    // ui->tabPlaceHolder->setVisible(false);
    // ui->gridLayout_2->addWidget(m_modelviewtabs);
    m_modelsDialog = new ModelsDialog(this);

    connect(m_modelsDialog, &ModelsDialog::planeClicked, this, &Widget::onPlaneClicked);
    connect(m_modelsDialog, &ModelsDialog::cubeClicked, this, &Widget::onCubeClicked);
    connect(m_modelsDialog, &ModelsDialog::torusClicked, this, &Widget::onTorusClicked);
    connect(m_modelsDialog, &ModelsDialog::loadObjClicked, this, &Widget::onLoadObjClicked);
    m_modelsDialog->show();
    qDebug() << "Add Model button clicked!";
}




void Widget::onPlaneClicked()
{
    BaseModel * plane_model =  new Plane("Plane");
    // qDebug() << "Plane Model Created!";

    m_models.push_back(plane_model);

    qDebug() << "Plane Model Pushed Back!";

    qDebug() << "Plane button clicked!";
    QIcon icon(":/icons/plane.png");
    addModelItemToTree("Plane", icon,plane_model);
}

void Widget::onCubeClicked()
{   

    qDebug() << "Cube button clicked!";
    QIcon icon(":/icons/cube.png");
    addModelItemToTree("Cube", icon,nullptr);
}

void Widget::onTorusClicked()
{
    qDebug() << "Torus button clicked!";
    QIcon icon(":/icons/torus.png");
    addModelItemToTree("Torus", icon,nullptr);
}

void Widget::onLoadObjClicked()
{
    qDebug() << "Load OBJ button clicked!";
    QIcon icon(":/icons/obj.png");
    addModelItemToTree("ObjModel", icon,nullptr);
}



void Widget::addModelItemToTree(const QString &name, const QIcon &icon, BaseModel *model)
{
    QTreeWidgetItem *rootItem = ui->modelsTree->topLevelItem(0);
    if (!rootItem) return;

    QTreeWidgetItem *childItem = new QTreeWidgetItem();
    childItem->setText(0, name);
    childItem->setIcon(0, icon);
    if(model){
        childItem->setData(0, Qt::UserRole, QVariant::fromValue(static_cast<void *>(model)));
    }

    rootItem->addChild(childItem);
    rootItem->setExpanded(true);
}


void Widget::onModelItemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if (!item) return;

    QVariant var = item->data(0, Qt::UserRole);
    if (!var.isValid()) {
        qDebug() << "No model pointer stored!";
        return;
    }

    BaseModel *model = static_cast<BaseModel *>(var.value<void *>());
    if (model && !model->isTabOpened()) {
        qDebug() << "Clicked model:" << model->m_name;
        ui->gridLayout_2->addWidget(m_modelviewtabs);
        m_modelviewtabs->addTab(model->getTab(), model->m_name + "Tab");
        model->draw();
        model->setTabOpened(true);
        ui->tabPlaceHolder->setVisible(false);
        // You can call model->draw(), rotate, etc.
    }
}

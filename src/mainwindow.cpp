#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include "Models.h"
#include "ObjLoader.h"
#include "ObjModel.h"
#include "ModelView.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
    m_modelviewtabs(new ModelViewTabs(this)),
    lightDir(0.0f, 0.0f, 1.0f)
{
    ui->setupUi(this);
    m_timer.setInterval(33); // ~33 ms → about 30 FPS (1000 ms / 30 ≈ 33.3)
    
    connect(ui->addModelBtn, &QPushButton::clicked,this, onAddModelBtnClicked);
    connect(&m_timer, &QTimer::timeout, this, update);
    QTreeWidgetItem *rootItem = new QTreeWidgetItem();
    QIcon icon(":/icons/3d-model.png");
    rootItem->setText(0, "Models");
    rootItem->setIcon(0, icon);
    ui->modelsTree->setIconSize(QSize(30, 30));  // Example: 48x48 icon
    ui->modelsTree->addTopLevelItem(rootItem);
    ui->modelsTree->setHeaderHidden(true);
    connect(ui->modelsTree, &QTreeWidget::itemClicked, this, &Widget::onModelItemClicked);
    m_timer.start();

}


void Widget::update(){
    std::lock_guard<std::mutex> lock(m_modelsMutex);
    for(auto model : m_models){
        if (model->isTabActive()){
            model->rotateY(1.0 / 180 * M_PI);
            model->rotateX(1.0 / 180 * M_PI);
            model->rotateZ(1.0 / 180 * M_PI);
            model->draw(lightDir);
        }
    }
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
    connect(m_modelsDialog, &ModelsDialog::coneClicked, this, &Widget::onconeClicked);
    m_modelsDialog->show();
    qDebug() << "Add Model button clicked!";
}


void Widget::addModel( BaseModel* model ){
    std::lock_guard<std::mutex> lock(m_modelsMutex);
    m_models.push_back(model);
}

QString Widget::askForModelName(const QString& defaultValue)
{
    QString name = QInputDialog::getText(
        this,
        "Enter Model Name",
        "Model name:",
        QLineEdit::Normal,
        defaultValue
    );

    return name; // Returns empty string if user cancels
}

void Widget::onPlaneClicked()
{
    QString name = askForModelName("PlanModel");
    BaseModel * plane_model =  new Plane(name);
    addModel(plane_model);
    qDebug() << "Plane Model Created!";


    qDebug() << "Plane Model Pushed Back!";

    qDebug() << "Plane button clicked!";
    QIcon icon(":/icons/plane.png");
    addModelItemToTree(name, icon,plane_model);
}

void Widget::onCubeClicked()
{   
    QString name = askForModelName("CubeModel");
    qDebug() << "Cube button clicked!";
    BaseModel * cube_model =  new Cube(name);
    addModel(cube_model);
    QIcon icon(":/icons/cube.png");
    addModelItemToTree(name, icon,cube_model);
}

void Widget::onTorusClicked()
{
    QString name = askForModelName("TorusModel");
    qDebug() << "Torus button clicked!";
    BaseModel * torus_model =  new Torus(name);
    addModel(torus_model);
    QIcon icon(":/icons/torus.png");
    addModelItemToTree(name, icon,torus_model);
}

void Widget::onconeClicked()
{
    QString name = askForModelName("coneModel");
    qDebug() << "cone button clicked!";
    BaseModel * cone_model =  new Cone(name);
    addModel(cone_model);
    QIcon icon(":/icons/cone.png");
    addModelItemToTree(name, icon,cone_model);
}

void Widget::onLoadObjClicked()
{
    QString name = askForModelName("ObjModel");
    qDebug() << "Load OBJ button clicked!";
    QIcon icon(":/icons/obj.png");
    QString filePath = QFileDialog::getOpenFileName(
    this,                              
    "Select OBJ File",                 
    "",                                
    "OBJ Files (*.obj);;All Files (*)" 
);

    ObjModel * obj_model = new ObjModel(name, filePath.toStdString());
    addModel(obj_model);
    addModelItemToTree(name, icon,obj_model);
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
        m_modelviewtabs->addTab(model->getTab(), model->m_name);
        model->setTabOpened(true);
        ui->tabPlaceHolder->setVisible(false);
        // You can call model->draw(), rotate, etc.
    }
}

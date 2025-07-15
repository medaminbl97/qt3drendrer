#include "ModelsDialog.h"
#include "ui_modelsdialog.h"

ModelsDialog::ModelsDialog(QWidget *parent)
    : QDialog{parent}
    ,ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->planeBtn, &QPushButton::clicked, this, &ModelsDialog::planeClicked);
    connect(ui->cubeBtn, &QPushButton::clicked, this, &ModelsDialog::cubeClicked);
    connect(ui->torusBtn, &QPushButton::clicked, this, &ModelsDialog::torusClicked);
    connect(ui->pyramidBtn, &QPushButton::clicked, this, &ModelsDialog::pyramidClicked);
    connect(ui->loadObjBtn, &QPushButton::clicked, this, &ModelsDialog::loadObjClicked);
}


ModelsDialog::~ModelsDialog()
{
    delete ui;
}

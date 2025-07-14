#include "ModelViewTabs.h"
#include "ui_modelviewtabs.h"
#include <QPainter>

ModelViewTabs::ModelViewTabs(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModelViewTabs)
{
    ui->setupUi(this);
    delete ui->tab;
    delete ui->tab_2;
}



ModelViewTabs::~ModelViewTabs()
{
    delete ui;
}

void ModelViewTabs::addTab(ModelView * new_tab, const QString& name){
    if(new_tab)
    {
        ui->tabWidget->addTab(new_tab,name);
    }
}

int ModelViewTabs::currentIndex() const
{
    return ui->tabWidget->currentIndex();
}
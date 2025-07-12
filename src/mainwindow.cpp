#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->addModelBtn, &QPushButton::clicked,
        this, onAddModelBtnClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onAddModelBtnClicked()
{   
    ui->tabPlaceHolder->setVisible(false);
    mv = new ModelView(this);
    ui->gridLayout_2->addWidget(mv);
    qDebug() << "Add Model button clicked!";
}
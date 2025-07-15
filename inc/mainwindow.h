#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <vector>
#include <mutex>
#include <QWidget>
#include <QTimer>
#include <QTreeWidgetItem>
#include "ModelViewTabs.h"
#include "ModelsDialog.h"
#include "BaseModel.h"
#include "Vec3.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    std::vector< BaseModel* > m_models;
    QTimer m_timer;
    std::mutex m_modelsMutex; 
    Vec3 lightDir;
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void onAddModelBtnClicked();
    void addModelItemToTree(const QString &name, const QIcon &icon, BaseModel *model);
    void onModelItemClicked(QTreeWidgetItem *item, int column);
    void update();
    void addModel( BaseModel* model);
    QString askForModelName(const QString& defaultValue = "YourModelName");



private slots:
    void onPlaneClicked();
    void onCubeClicked();
    void onTorusClicked();
    void onLoadObjClicked();
    void onconeClicked();


private:
    Ui::Widget *ui;
    ModelViewTabs * m_modelviewtabs;
    ModelsDialog * m_modelsDialog;
};

#endif // MAINWINDOW_H

#ifndef MODELVIEWTABS_H
#define MODELVIEWTABS_H

#include <QWidget>
#include "ModelView.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ModelViewTabs; }
QT_END_NAMESPACE

class ModelViewTabs : public QWidget
{
    Q_OBJECT

public:
    explicit ModelViewTabs(QWidget *parent = nullptr);
    ~ModelViewTabs();
    void addTab(ModelView * new_tab, const QString& name);
    int currentIndex()const;


private:
    Ui::ModelViewTabs *ui;
};

#endif // MODELVIEWTABS_H

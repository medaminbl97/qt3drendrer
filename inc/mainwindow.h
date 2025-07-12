#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "modelview.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void onAddModelBtnClicked();

private:
    Ui::Widget *ui;
    ModelView * mv;
};

#endif // MAINWINDOW_H

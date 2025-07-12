#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class ModelView : public QWidget
{
    Q_OBJECT

public:
    explicit ModelView(QWidget *parent = nullptr);
    ~ModelView();
    void drawCircle();


private:
    Ui::Form *ui;
};

#endif // MODELVIEW_H

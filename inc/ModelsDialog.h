#ifndef MODELSDIALOG_H
#define MODELSDIALOG_H

#include <QWidget>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE
class ModelsDialog: public QDialog
{
    Q_OBJECT

public:
    explicit ModelsDialog(QWidget *parent = nullptr);
    ~ModelsDialog();
public: signals:
    void planeClicked();
    void cubeClicked();
    void torusClicked();
    void coneClicked();
    void loadObjClicked();

private:
    Ui::Dialog *ui;
};

#endif // MODELSDIALOG_H


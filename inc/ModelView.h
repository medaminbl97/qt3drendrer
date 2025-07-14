#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QWidget>
#include "Polygon.h"
#include "TransformMatrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ModelView; }
QT_END_NAMESPACE

class ModelView : public QWidget
{
    Q_OBJECT

public:
    explicit ModelView(QWidget *parent = nullptr);
    ~ModelView();
    void setUpToolBtns();
    void draw(const std::vector<Polygon>& mesh) const;
    QPoint getOrigin() const;



private:
    Ui::ModelView *ui;
};

#endif // MODELVIEW_H

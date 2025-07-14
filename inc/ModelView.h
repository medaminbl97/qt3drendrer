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
    void draw(const std::vector<Polygon>& mesh, const QString& model_name) const;
    bool isActive() const;
    QPoint getOrigin() const;
    void update();
    
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    
    
private:
    Ui::ModelView *ui;
    bool m_tabActive;
};

#endif // MODELVIEW_H

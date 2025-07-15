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
    struct Gizmo {
        Vec3 x;
        Vec3 y;
        Vec3 z;
    };

public:
    explicit ModelView(QWidget *parent = nullptr);
    ~ModelView();
    void setUpToolBtns();
    void draw(const std::vector<Polygon>& mesh, const QString& model_name, const Vec3& light);
    void rotateGizmo(const QString& axisLabel, float angleDegrees);
    void drawGizmo(QPainter& painter);

    
    bool isActive() const;
    QPoint getOrigin() const;
    void update();
    void openColorDialog();

    void onRotatex();
    void onRotatey();
    void onRotatez();
    
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    
public:
    bool rotatex;
    bool rotatey;
    bool rotatez;
private:
    Ui::ModelView *ui;
    bool m_tabActive;
    QColor m_color;
    Gizmo m_gizmo;

};

#endif // MODELVIEW_H

#pragma once

#include <thread>
#include <mutex>
#include <atomic>

#include <QGraphicsView>
#include <QTimer>
#include <QPoint>
#include "Polygon.h"
#include "TransformMatrix.h"
#include "ModelView.h"
#include "QColor.h"

class BaseModel
{
public:
    QString m_name;
protected:
    QTimer m_timer;
    std::vector<Polygon> mesh;
    ModelView * m_modelview;
    bool m_tabOpened;

    // std::unique_ptr<std::thread> m_workerThread;
    // std::mutex m_meshMutex;
    // std::atomic<bool> m_running;

    // std::function<void()> m_singleShotFunc;
    // bool m_singleShotMode;

public:
    BaseModel(const QString& name = "no_name");
    void loadModelFromOBJ(const std::string& path);
    ModelView * getTab();
    bool isTabOpened() const;
    void setTabOpened(bool value);
    bool isTabActive()const;
    QColor getColor()const;
    virtual ~BaseModel() = 0;
    virtual void draw(const Vec3& light);
    virtual void rotateX(float angle);
    virtual void rotateY(float angle);
    virtual void rotateZ(float angle);


    // void startWorker(bool singleShot = false, std::function<void()> func = nullptr);
    // void stopWorker();

private:
    // void workerLoop();
    QPoint getOrigin() const;
};


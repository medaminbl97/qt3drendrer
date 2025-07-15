#include "BaseModel.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <QVBoxLayout>



BaseModel::BaseModel(const QString& name)
 :  m_name(name), m_tabOpened(false), m_modelview(new ModelView())//, m_running(false), m_singleShotMode(false)
{   
}

void BaseModel::setTabOpened(bool value)
{
    m_tabOpened = value;
}

bool BaseModel::isTabActive() const
{
    return m_modelview->isActive();
}

bool BaseModel::isTabOpened() const
{
    return m_tabOpened;
}

BaseModel::~BaseModel() = default;

void BaseModel::draw(const Vec3& light)
{
    m_modelview->draw(mesh,m_name,light);
}

void BaseModel::rotateX(float angle)
{
    if(!m_modelview->rotatex) return;
    m_modelview->rotateGizmo("X",angle);
    qDebug() << "Rotating around X axis!";
    for (auto& poly : mesh)
    {
        TransformMatrix::rotatePolygonX(poly,angle);
    }
}
void BaseModel::rotateY(float angle)
{
    if(!m_modelview->rotatey) return;
    m_modelview->rotateGizmo("Y",angle);
    qDebug() << "Rotating around Y axis!";
        for (auto& poly : mesh)
    {
        TransformMatrix::rotatePolygonY(poly,angle);
    }
}

void BaseModel::rotateZ(float angle)
{
    if(!m_modelview->rotatez) return;
    m_modelview->rotateGizmo("Z",angle);

    qDebug() << "Rotating around Z axis!";
    for (auto& poly : mesh)
    {
        TransformMatrix::rotatePolygonZ(poly,angle);
    }
}


ModelView *BaseModel::getTab()
{   
    m_modelview->setObjectName("Model Tab");
    return m_modelview;
}



// void BaseModel::startWorker(bool singleShot, std::function<void()> func)
// {
//     if (m_running.load()) {
//         qDebug() << "Worker already running";
//         return;
//     }

//     m_singleShotMode = singleShot;
//     m_singleShotFunc = func;
//     m_running = true;

//     m_workerThread = std::make_unique<std::thread>(&BaseModel::workerLoop, this);
// }

// void BaseModel::stopWorker()
// {
//     if (m_running.load()) {
//         m_running = false;
//         if (m_workerThread && m_workerThread->joinable()) {
//             m_workerThread->join();
//         }
//     }
// }

// void BaseModel::workerLoop()
// {
//     if (m_singleShotMode && m_singleShotFunc) {
//         {
//             std::lock_guard<std::mutex> lock(m_meshMutex);
//             m_singleShotFunc();
//         }

//         if (m_modelview) {
//             QMetaObject::invokeMethod(m_modelview, "update", Qt::QueuedConnection);
//         }

//         m_running = false;
//         return;
//     }

//     while (m_running.load()) {
//         {
//             std::lock_guard<std::mutex> lock(m_meshMutex);
//             // Example: continuous rotation
//             this->rotateY(0.05f);
//         }

//         if (m_modelview) {
//             QMetaObject::invokeMethod(m_modelview, "update", Qt::QueuedConnection);
//         }

//         std::this_thread::sleep_for(std::chrono::milliseconds(30));
//     }
// }
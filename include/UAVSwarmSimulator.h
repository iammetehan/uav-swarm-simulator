#ifndef UAVSWARMSIMULATOR_H
#define UAVSWARMSIMULATOR_H

#include "Scene.h"
#include "Definitions.h"
#include "UAV.h"
#include "Threat.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QUdpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class UAVSwarmSimulator; }
QT_END_NAMESPACE

class UAVSwarmSimulator : public QMainWindow
{
    Q_OBJECT

public:
    UAVSwarmSimulator(QWidget *parent = nullptr);
    ~UAVSwarmSimulator();

private:
    void SetDefaultSwarm();
    void AddItemsToScene();
    void RemoveItemsFromScene();

private:
    void SendMapPointData() const;
    void SendThreatData() const;
    void SendSrcDstData(const QPointF &src, const QPointF &dst) const;
    void SendFindPathMsg() const;
    void FindPath(const QPointF& src, const QPointF& dst) const;
    QList<int> ConvertToIntPaths(const QList<bool> boolPoints) const;

private:
    void AddDefMission();
    void AddDefSimItems();
    void AddDefUAVModels();
    void AddDefThreatTypes();

private:
    void AddUAVModel(Item::UAV* uavModel);
    void AddThreatType(Item::Threat* threatType);

private:
    void SetMap(const Data::Map &map);

private:
    void SetDestinations();

private slots:
    void SelectMap();
    void AddNewUAV();
    void AddNewThreat();
    void ManageSwarm();
    void ManageMission();
    void StartSimulation();
    void DoStep();
    void StopSimulation();
    void UpdateServer();
    void FindPaths();
    void ReadPaths();

signals:
    void UAVProcessed();

private:
    QTimer m_timer;
    const int m_timeOut = 100; // ms

private:
    Display::Scene* m_scene;

private:
    QList<Item::UAV *> m_UAVModels;
    QList<Item::Threat *> m_threatTypes;

private:
    QList<Item::UAV *> m_UAVs;
    QList<Item::Threat *> m_threats;

private:
    Item::Mission* m_mission;

private:
    Item::UAV* m_currProcessedUAV = nullptr;

private:
    QUdpSocket* m_listen;

private:
    Ui::UAVSwarmSimulator *ui;
};
#endif // UAVSWARMSIMULATOR_H

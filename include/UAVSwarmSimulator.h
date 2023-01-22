#ifndef UAVSWARMSIMULATOR_H
#define UAVSWARMSIMULATOR_H

#include "Scene.h"
#include "Definitions.h"
#include "UAV.h"
#include "Threat.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class UAVSwarmSimulator; }
QT_END_NAMESPACE

class UAVSwarmSimulator : public QMainWindow
{
    Q_OBJECT

public:
    UAVSwarmSimulator(QWidget *parent = nullptr);
    ~UAVSwarmSimulator();

public:
    void SetDefaultSwarm();
    void SetDefaultPositions();

private:
    void AddDefSimItems();
    void AddDefUAVModels();
    void AddDefThreatTypes();

private:
    void AddUAVModel(Item::UAV* uavModel);
    void AddThreatType(Item::Threat* threatType);

private:
    void SetMap(const Data::Map &map);

private slots:
    void SelectMap();
    void AddNewUAV();
    void AddNewThreat();
    void ManageSwarm();
    void StartSimulation();
    void DoStep();
    void StopSimulation();

private:
    QTimer timer;
    const int timeOut = 100; // ms

private:
    Display::Scene* m_scene;

private:
    QList<Item::UAV *> m_UAVModels;
    QList<Item::Threat *> m_threadTypes;

private:
    QList<Item::UAV *> m_UAVs;
    QList<Item::Threat *> m_threats;

private:
    Ui::UAVSwarmSimulator *ui;
};
#endif // UAVSWARMSIMULATOR_H

#ifndef UAVSWARMSIMULATOR_H
#define UAVSWARMSIMULATOR_H

#include "Scene.h"
#include "Definitions.h"
#include "UAV.h"
#include "Threat.h"

#include <QMainWindow>
#include <QGraphicsScene>

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
    void AddDefSimItems();
    void AddDefUAVModels();
    void AddDefThreatTypes();

private:
    void AddUAVModel(Item::UAV* uavModel);
    void AddThreatType(Item::Threat* threatType);

private slots:
    void SelectMap();
    void AddNewUAV();
    void AddNewThreat();
    void ManageSwarm();

private:
    Data::Map m_map;
    Display::Scene* m_scene;

private:
    QList<Item::UAV *> m_UAVModels;
    QList<Item::Threat *> m_threadTypes;

private:
    QList<Item::UAV *> m_UAVs;
    QList<Item::Threat *> m_threads;

private:
    Ui::UAVSwarmSimulator *ui;
};
#endif // UAVSWARMSIMULATOR_H

#ifndef UAVSWARMSIMULATOR_H
#define UAVSWARMSIMULATOR_H

#include "Definitions.h"
#include "Scene.h"
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
    Data::Map m_map;
    Display::Scene* m_scene;


private slots:
    void SelectMap();
    void AddNewUAV();
    void AddNewThreat();
    void ManageSwarm();

private:
    Ui::UAVSwarmSimulator *ui;
};
#endif // UAVSWARMSIMULATOR_H

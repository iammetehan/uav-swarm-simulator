#ifndef UAVSWARMSIMULATOR_H
#define UAVSWARMSIMULATOR_H

#include "Definitions.h"
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
    QGraphicsScene* m_scene;

private slots:
    void SelectMap();

private:
    Ui::UAVSwarmSimulator *ui;
};
#endif // UAVSWARMSIMULATOR_H

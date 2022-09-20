#include "ui_UAVSwarmSimulator.h"
#include "UAVSwarmSimulator.h"

#include "SelectMapDialog.h"
#include "AddNewUAVDialog.h"
#include "AddNewThreatDialog.h"
#include "ManageSwarmDialog.h"

#include <QDebug>

UAVSwarmSimulator::UAVSwarmSimulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UAVSwarmSimulator)
{
    ui->setupUi(this);

    m_scene = new Display::Scene(this);
    ui->view->setScene(m_scene);

    AddDefSimItems();

    connect(ui->selectMap, SIGNAL(clicked()), this, SLOT(SelectMap()));
    connect(ui->addNewUAV, SIGNAL(clicked()), this, SLOT(AddNewUAV()));
    connect(ui->addNewThreat, SIGNAL(clicked()), this, SLOT(AddNewThreat()));
    connect(ui->manageSwarm, SIGNAL(clicked()), this, SLOT(ManageSwarm()));
}

void UAVSwarmSimulator::AddDefSimItems()
{
    AddDefUAVModels();
    AddDefThreatTypes();
}

void UAVSwarmSimulator::AddDefUAVModels()
{
    AddUAVModel(new Item::UAV(QString("DJI 1"),
                          QImage("D:/images/DJI1.png")));
    AddUAVModel(new Item::UAV(QString("DJI 2"),
                          QImage("D:/images/DJI2.png")));
    AddUAVModel(new Item::UAV(QString("DJI 3"),
                          QImage("D:/images/DJI3.png")));
}

void UAVSwarmSimulator::AddDefThreatTypes()
{
    AddThreatType(new Item::Threat(QString("Terrorist Group"),
                                   50.0,
                                   70.0,
                                   QColor(Qt::red)));

    AddThreatType(new Item::Threat(QString("Air Defense Missiles"),
                                   100.0,
                                   120.0,
                                   QColor(Qt::blue)));
}

void UAVSwarmSimulator::AddUAVModel(Item::UAV* uavModel)
{
    m_UAVModels.append(uavModel);
}

void UAVSwarmSimulator::AddThreatType(Item::Threat* threatType)
{
    m_threadTypes.append(threatType);
}

void UAVSwarmSimulator::SelectMap()
{
    SelectMapDialog selectMapDialog;
    if (QDialog::Accepted == selectMapDialog.exec())
    {
        m_map = selectMapDialog.Map();
        m_scene->addPixmap(QPixmap::fromImage(m_map.Image()));
    }
}

void UAVSwarmSimulator::AddNewUAV()
{
    AddNewUAVDialog addNewUAVDialog;
    if (QDialog::Accepted == addNewUAVDialog.exec())
    {

    }
}

void UAVSwarmSimulator::AddNewThreat()
{
    AddNewThreatDialog addNewThreatDialog;
    if (QDialog::Accepted == addNewThreatDialog.exec())
    {

    }
}

void UAVSwarmSimulator::ManageSwarm()
{
    ManageSwarmDialog manageSwarmDialog(m_UAVModels, m_threadTypes);
    if (QDialog::Accepted == manageSwarmDialog.exec())
    {

    }
}

UAVSwarmSimulator::~UAVSwarmSimulator()
{
    delete ui;
}

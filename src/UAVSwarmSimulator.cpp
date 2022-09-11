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

    connect(ui->selectMap, SIGNAL(clicked()), this, SLOT(SelectMap()));
    connect(ui->addNewUAV, SIGNAL(clicked()), this, SLOT(AddNewUAV()));
    connect(ui->addNewThreat, SIGNAL(clicked()), this, SLOT(AddNewThreat()));
    connect(ui->manageSwarm, SIGNAL(clicked()), this, SLOT(ManageSwarm()));
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
    ManageSwarmDialog manageSwarmDialog;
    if (QDialog::Accepted == manageSwarmDialog.exec())
    {

    }
}

UAVSwarmSimulator::~UAVSwarmSimulator()
{
    delete ui;
}


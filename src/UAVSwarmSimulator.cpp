#include <UAVSwarmSimulator.h>
#include "ui_UAVSwarmSimulator.h"
#include "SelectMapDialog.h"
#include <QDebug>

UAVSwarmSimulator::UAVSwarmSimulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UAVSwarmSimulator)
{
    ui->setupUi(this);

    connect(ui->selectMap, SIGNAL(clicked()), this, SLOT(SelectMap()));
}

void UAVSwarmSimulator::SelectMap()
{
    SelectMapDialog selectMapDialog;
    if (QDialog::Accepted == selectMapDialog.exec())
    {
        m_map = selectMapDialog.Map();
    }
}

UAVSwarmSimulator::~UAVSwarmSimulator()
{
    delete ui;
}


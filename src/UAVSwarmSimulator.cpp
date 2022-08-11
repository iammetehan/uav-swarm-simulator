#include <UAVSwarmSimulator.h>
#include "ui_UAVSwarmSimulator.h"

UAVSwarmSimulator::UAVSwarmSimulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UAVSwarmSimulator)
{
    ui->setupUi(this);
}

UAVSwarmSimulator::~UAVSwarmSimulator()
{
    delete ui;
}


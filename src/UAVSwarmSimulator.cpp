#include <UAVSwarmSimulator.h>
#include "ui_UAVSwarmSimulator.h"
#include "SelectMapDialog.h"
#include <QDebug>

UAVSwarmSimulator::UAVSwarmSimulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UAVSwarmSimulator)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    ui->view->setScene(m_scene);

    connect(ui->selectMap, SIGNAL(clicked()), this, SLOT(SelectMap()));
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

UAVSwarmSimulator::~UAVSwarmSimulator()
{
    delete ui;
}


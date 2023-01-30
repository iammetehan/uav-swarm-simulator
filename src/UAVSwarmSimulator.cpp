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
    SetDefaultSwarm();

    connect(ui->selectMap, SIGNAL(clicked()), this, SLOT(SelectMap()));
    connect(ui->addNewUAV, SIGNAL(clicked()), this, SLOT(AddNewUAV()));
    connect(ui->addNewThreat, SIGNAL(clicked()), this, SLOT(AddNewThreat()));
    connect(ui->manageSwarm, SIGNAL(clicked()), this, SLOT(ManageSwarm()));
    connect(ui->startSimulation, SIGNAL(clicked()), this, SLOT(StartSimulation()));
    connect(ui->stopSimulation, SIGNAL(clicked()), this, SLOT(StopSimulation()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(DoStep()));


    connect(ui->findPaths, SIGNAL(clicked()), this, SLOT(FindPaths()));

    listen = new QUdpSocket(this);
    listen->bind(QHostAddress::LocalHost, 7755);

    connect(listen, &QUdpSocket::readyRead,
            this, &UAVSwarmSimulator::ReadPaths);

}

void UAVSwarmSimulator::AddDefSimItems()
{
    AddDefUAVModels();
    AddDefThreatTypes();
}

void UAVSwarmSimulator::AddDefUAVModels()
{
    AddUAVModel(new Item::UAV(QString("DJI 1"),
                              QColor(Qt::red),
                              10,
                              20));
    AddUAVModel(new Item::UAV(QString("DJI 2"),
                              QColor(Qt::green),
                              10,
                              20));
    AddUAVModel(new Item::UAV(QString("DJI 3"),
                              QColor(Qt::blue),
                              10,
                              20));
}

void UAVSwarmSimulator::AddDefThreatTypes()
{
    AddThreatType(new Item::Threat(QString("Terrorist Group"),
                                   200,
                                   250,
                                   QColor(Qt::red)));

    AddThreatType(new Item::Threat(QString("Air Defense Missiles"),
                                   270,
                                   320,
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

void UAVSwarmSimulator::SetMap(const Data::Map &map)
{
    m_scene->SetMap(map);
    m_scene->setSceneRect(map.Image().rect());
}

void UAVSwarmSimulator::SelectMap()
{
    SelectMapDialog selectMapDialog;
    if (QDialog::Accepted == selectMapDialog.exec())
    {
        SetMap(selectMapDialog.Map());
    }
}

void UAVSwarmSimulator::SetDefaultSwarm()
{
    using namespace Item;

    SetMap(Data::Map(500,
                     400,
                     100,
                     "D:/images/map1.PNG"));

    for (const UAV* uav: m_UAVModels)
    {
        m_UAVs.append(ManageSwarmDialog::GetUAVInstances(uav, 3));
    }

    for (UAV* uav: m_UAVs)
    {
        int numOfPoints = rand() % 10;
        QVector<QPointF> path;
        for (int i = 0; i < numOfPoints; i++)
        {
            path.append(m_scene->Map().Points().at(rand() % m_scene->Map().Points().size()));
        }
        uav->SetPath(path);

    }

    for (const Threat* threat: m_threadTypes)
    {
        m_threats.append(ManageSwarmDialog::GetThreatInstances(threat, 3));
    }

    SetDefaultPositions();
}

void UAVSwarmSimulator::SetDefaultPositions()
{
    using namespace Item;

    int a = 5;
    for (UAV* uav: m_UAVs)
    {
        m_scene->addItem(uav);
        uav->setPos(a, a);
        a += 50;
    }

    for (Threat* threat: m_threats)
    {
        m_scene->addItem(threat);
        threat->setPos(a, a);
        a += 50;
    }
}

void UAVSwarmSimulator::AddNewUAV()
{
    AddNewUAVDialog addNewUAVDialog;
    if (QDialog::Accepted == addNewUAVDialog.exec())
    {
        AddUAVModel(addNewUAVDialog.NewUAV());
    }
}

void UAVSwarmSimulator::AddNewThreat()
{
    AddNewThreatDialog addNewThreatDialog;
    if (QDialog::Accepted == addNewThreatDialog.exec())
    {
        AddThreatType(addNewThreatDialog.NewThreat());
    }
}

void UAVSwarmSimulator::ManageSwarm()
{
    using namespace Item;

    ManageSwarmDialog manageSwarmDialog(m_UAVModels, m_threadTypes);
    if (QDialog::Accepted == manageSwarmDialog.exec())
    {
        m_UAVs = manageSwarmDialog.GetUAVs();
        m_threats = manageSwarmDialog.GetThreats();

        SetDefaultPositions();
    }
}

void UAVSwarmSimulator::StartSimulation()
{
    timer.start(timeOut);
}

void UAVSwarmSimulator::DoStep()
{
    using namespace Item;
    qDebug() << "Updated";

    for(UAV* uav: m_UAVs)
    {
        uav->Step();
    }

}

void UAVSwarmSimulator::StopSimulation()
{
    timer.stop();
}

void UAVSwarmSimulator::FindPaths()
{
    QByteArray mapPointData;
    QDataStream mapPointDataStream(&mapPointData, QIODevice::WriteOnly);
    mapPointDataStream << m_scene->Map().Points().size() * 2;

    for (const QPointF& p: m_scene->Map().Points())
    {
        mapPointDataStream << p.x();
        mapPointDataStream << p.y();
    }

    QUdpSocket mapSocket;
    mapSocket.writeDatagram(mapPointData.data(), mapPointData.size(), QHostAddress::LocalHost, 4651);

    QByteArray threatPointData;
    QDataStream threatPointDataStream(&threatPointData, QIODevice::WriteOnly);
    threatPointDataStream << m_threats.size();

    for (Item::Threat* threat: m_threats)
    {
        threatPointDataStream << threat->sceneBoundingRect().topLeft().x();
        threatPointDataStream << threat->sceneBoundingRect().topLeft().y();

        threatPointDataStream << threat->sceneBoundingRect().topRight().x();
        threatPointDataStream << threat->sceneBoundingRect().topRight().y();

        threatPointDataStream << threat->sceneBoundingRect().bottomRight().x();
        threatPointDataStream << threat->sceneBoundingRect().bottomRight().y();

        threatPointDataStream << threat->sceneBoundingRect().bottomLeft().x();
        threatPointDataStream << threat->sceneBoundingRect().bottomLeft().y();
    }


    QUdpSocket threatSocket;
    threatSocket.writeDatagram(threatPointData.data(), threatPointData.size(), QHostAddress::LocalHost, 4652);
}


void UAVSwarmSimulator::ReadPaths()
{
    QByteArray datagram;
    while (listen->hasPendingDatagrams())
    {
        datagram.resize(listen->pendingDatagramSize());
        listen->readDatagram(datagram.data(),datagram.size());
    }

    qDebug() << datagram;
}


UAVSwarmSimulator::~UAVSwarmSimulator()
{
    delete ui;
}

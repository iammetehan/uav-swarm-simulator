#include "ui_UAVSwarmSimulator.h"
#include "UAVSwarmSimulator.h"

#include "SelectMapDialog.h"
#include "AddNewUAVDialog.h"
#include "AddNewThreatDialog.h"
#include "ManageSwarmDialog.h"

#include <iterator>
#include <QDebug>
#include <QThread>


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
    connect(ui->updateServer, SIGNAL(clicked()), this, SLOT(UpdateServer()));
    connect(ui->findPaths, SIGNAL(clicked()), this, SLOT(FindPaths()));

    listen = new QUdpSocket(this);
    listen->bind(QHostAddress::LocalHost, 4655);

    connect(listen, &QUdpSocket::readyRead,
            this, &UAVSwarmSimulator::ReadPaths);

    connect(this, &UAVSwarmSimulator::UAVProcessed,
            this, &UAVSwarmSimulator::FindPaths);

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
        m_UAVs.append(ManageSwarmDialog::GetUAVInstances(uav, 1));
    }

    for (UAV* uav: m_UAVs)
    {
        int numOfPoints = rand() % 10;
        QVector<QPointF> path;
        for (int i = 0; i < numOfPoints; i++)
        {
            path.append(m_scene->Map().Points().at(rand() % m_scene->Map().Points().size()));
        }
        uav->SetDestination(QPointF(700, 700));
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
    using namespace Item;

    for(UAV* uav: m_UAVs)
    {
        uav->BeforeSimulation();
    }

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

    m_scene->invalidate(Item::SceneRect());
}

void UAVSwarmSimulator::StopSimulation()
{
    using namespace Item;

    timer.stop();

    for(UAV* uav: m_UAVs)
    {
        uav->AfterSimulation();
    }
}

void UAVSwarmSimulator::UpdateServer()
{
    SendMapPointData();
    SendThreatData();
}

void UAVSwarmSimulator::FindPaths()
{
    using namespace Item;

    qDebug() << "1";

    if (nullptr == m_currProcessedUAV)
    {
        qDebug() << "2";
        m_currProcessedUAV = m_UAVs.first();
    }
    else
    {
        if (m_currProcessedUAV == m_UAVs.last())
        {
            qDebug() << "3";
            m_currProcessedUAV = nullptr;
            return;
        }
        else
        {
            qDebug() << "4";
            int index = m_UAVs.indexOf(m_currProcessedUAV) + 1;
            m_currProcessedUAV = m_UAVs.at(index);
        }
    }

    FindPath(m_currProcessedUAV->Source(),
             m_currProcessedUAV->Destination());
}

void UAVSwarmSimulator::FindPath(const QPointF& src, const QPointF& dst) const
{
    SendSrcDstData(src, dst);
    SendFindPathMsg();
}

QList<int> UAVSwarmSimulator::ConvertToIntPaths(const QList<bool> boolPaths) const
{
    QList<int> intPaths;
    for (int i = 0; i < boolPaths.size(); i++)
    {
        if (boolPaths.at(i))
        {
            intPaths.append(i);
        }
    }
    return intPaths;
}

void UAVSwarmSimulator::SendMapPointData() const
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
}

void UAVSwarmSimulator::SendThreatData() const
{
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

void UAVSwarmSimulator::SendSrcDstData(const QPointF &src, const QPointF &dst) const
{
    QByteArray srcDstData;
    QDataStream srcDstDataStream(&srcDstData, QIODevice::WriteOnly);

    srcDstDataStream << src.x();
    srcDstDataStream << src.y();

    srcDstDataStream << dst.x();
    srcDstDataStream << dst.y();

    qDebug() << srcDstData.size();

    QUdpSocket srcDstSocket;
    srcDstSocket.writeDatagram(srcDstData.data(), srcDstData.size(), QHostAddress::LocalHost, 4653);
}

void UAVSwarmSimulator::SendFindPathMsg() const
{
    qDebug() << "SendFindPathMsg";

    QByteArray findPathData("FindPath");

    qDebug() << findPathData.size();

    QUdpSocket findPatSocket;
    findPatSocket.writeDatagram(findPathData.data(), findPathData.size(), QHostAddress::LocalHost, 4654);
}

void UAVSwarmSimulator::ReadPaths()
{
    QByteArray datagram;
    while (listen->hasPendingDatagrams())
    {
        datagram.resize(listen->pendingDatagramSize());
        listen->readDatagram(datagram.data(),datagram.size());
    }
    qDebug() << datagram.size();

    QVector<bool> boolData;
    for(int i = 0; i < datagram.size();i++)
    {
        boolData.append(datagram.at(i));
    }

    const int numberOfPaths = boolData.size() / (Data::Map::TotalNumOfPoints());

    QVector<QVector<bool>> boolPaths;
    for(int i = 0; i < numberOfPaths; i++)
    {
        QVector<bool> boolPath;
        for (int k = 0; k < Data::Map::TotalNumOfPoints(); k++)
        {
            const int index = (i * Data::Map::TotalNumOfPoints()) + k;
            boolPath.append(boolData.at(index));
        }
        boolPaths.append(boolPath);
    }

    QVector<QVector<int>> intPaths;
    for(const QVector<bool>& points: boolPaths)
    {
        intPaths.append(ConvertToIntPaths(points));
    }

    m_currProcessedUAV->SetPaths(m_scene->Map().IndexesToPaths(intPaths));
    emit UAVProcessed();
}

UAVSwarmSimulator::~UAVSwarmSimulator()
{
    delete ui;
}

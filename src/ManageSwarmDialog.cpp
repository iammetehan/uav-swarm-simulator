#include "ManageSwarmDialog.h"
#include "ui_ManageSwarmDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSpacerItem>
#include <QScrollArea>

ManageSwarmDialog::ManageSwarmDialog(const QList<Item::UAV *> &UAVModels,
                                     const QList<Item::Threat *> &threats,
                                     QWidget *parent) :
    QDialog(parent),
    m_UAVModels(UAVModels),
    m_threadTypes(threats),
    ui(new Ui::ManageSwarmDialog)
{
    ui->setupUi(this);

    connect(ui->OK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));

    CreateSimItemWidgets();
}

ManageSwarmDialog::~ManageSwarmDialog()
{
    delete ui;
}

void ManageSwarmDialog::CreateSimItemWidgets()
{
    CreateUAVModelWidgets();
    CreateThreatTypeWidgets();
}

void ManageSwarmDialog::CreateUAVModelWidgets()
{
    for (const Item::UAV* uavModel: m_UAVModels)
    {
        ui->addUAVLay->addWidget(GetItemWidget(uavModel->Model()));
    }
}

void ManageSwarmDialog::CreateThreatTypeWidgets()
{
    for (const Item::Threat* threatType: m_threadTypes)
    {
        ui->addThreatLay->addWidget(GetItemWidget(threatType->Type()));
    }
}

QWidget *ManageSwarmDialog::GetItemWidget(const QString& item)
{
    QWidget* widget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(widget);
    QLabel* label = new QLabel(widget);
    QSpinBox* spinBox = new QSpinBox(widget);

    label->setText(item);

    spinBox->setObjectName(item);
    spinBox->setMinimum(Item::MinNumOfItem());
    spinBox->setMaximum(Item::MaxNumOfItem());

    layout->addWidget(label);
    layout->addWidget(spinBox);

    return widget;
}

QList<Item::UAV *> ManageSwarmDialog::GetUAVs() const
{
    using namespace Item;

    QList<UAV *> UAVs;
    for (const UAV* uav: m_UAVModels)
    {
        QSpinBox* sBox = ui->addUAVWidget->findChild<QSpinBox*>(uav->Model());

        if (nullptr != sBox)
        {
            for (int i = 0; i < sBox->value(); i++)
            {
                UAVs.append(dynamic_cast<UAV *> (uav->Clone()));
            }
        }
    }

    return UAVs;
}

QList<Item::Threat *> ManageSwarmDialog::GetThreats() const
{
    using namespace Item;

    QList<Threat *> threats;
    for (const Threat* threat: m_threadTypes)
    {
        QSpinBox* sBox = ui->addThreatWidget->findChild<QSpinBox *>(threat->Type());

        if (nullptr != sBox)
        {
            for (int i = 0; i < sBox->value(); i++)
            {
                threats.append(dynamic_cast<Threat *> (threat->Clone()));
            }
        }
    }

    return threats;
}

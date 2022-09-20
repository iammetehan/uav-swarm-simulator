#include "ManageSwarmDialog.h"
#include "qlabel.h"
#include "ui_ManageSwarmDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>

ManageSwarmDialog::ManageSwarmDialog(const QList<Item::UAV *> &UAVModels,
                                     const QList<Item::Threat *> &threats,
                                     QWidget *parent) :
    QDialog(parent),
    m_UAVModels(UAVModels),
    m_threadTypes(threats),
    ui(new Ui::ManageSwarmDialog)
{
    ui->setupUi(this);
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
        ui->addUAVLay->addWidget(GetItemWidget(uavModel));
    }
}

void ManageSwarmDialog::CreateThreatTypeWidgets()
{
    for (const Item::Threat* threatType: m_threadTypes)
    {
        ui->addThreadLay->addWidget(GetItemWidget(threatType));
    }
}

QWidget *ManageSwarmDialog::GetItemWidget(const Item::SimItem* item)
{
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(widget);
    QLabel* label = new QLabel(item->Name());
    QSpinBox* spinBox = new QSpinBox();

    spinBox->setMinimum(Item::MinNumOfItem());
    spinBox->setMaximum(Item::MaxNumOfItem());

    layout->addWidget(label);
    layout->addWidget(spinBox);

    return widget;
}

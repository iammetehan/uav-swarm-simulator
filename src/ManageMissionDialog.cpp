#include "ManageMissionDialog.h"
#include "ui_ManageMissionDialog.h"

ManageMissionDialog::ManageMissionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageMissionDialog)
{
    ui->setupUi(this);

    ui->types->addItems(Item::MissionTypes());

    connect(ui->OK, SIGNAL(clicked()), this, SLOT(Accept()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void ManageMissionDialog::SetDefaultMission(Item::Mission *mission)
{
    m_mission = mission;

    ui->types->setCurrentText(mission->Type());
    ui->width->setText(QString::number(mission->Width()));
    ui->height->setText(QString::number(mission->Height()));
}

ManageMissionDialog::~ManageMissionDialog()
{
    delete ui;
}

void ManageMissionDialog::Accept()
{
    m_mission->SetType(ui->types->currentText());
    m_mission->SetWidth(ui->width->text().toDouble());
    m_mission->SetHeight(ui->height->text().toDouble());

    accept();
}

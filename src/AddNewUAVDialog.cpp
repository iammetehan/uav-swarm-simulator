#include "ui_AddNewUAVDialog.h"
#include "AddNewUAVDialog.h"
#include "UAV.h"
#include <QFileDialog>
#include <QColorDialog>

AddNewUAVDialog::AddNewUAVDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewUAVDialog)
{
    ui->setupUi(this);

    ui->speed->setValidator(Data::IntegerRegularExp());
    ui->batteryDuration->setValidator(Data::IntegerRegularExp());

    connect(ui->selectImage, SIGNAL(clicked()), this, SLOT(SelectImage()));
    connect(ui->OK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

AddNewUAVDialog::~AddNewUAVDialog()
{
    delete ui;
}

void AddNewUAVDialog::SelectColor()
{
    ui->selectedColor->setPalette(QPalette(QColorDialog::getColor()));
}


Item::UAV* AddNewUAVDialog::NewUAV()
{
    return new Item::UAV(ui->UAVModel->text(),
                         ui->selectedColor->palette().color(QPalette::ColorRole::Button),
                         ui->speed->text().toInt(),
                         ui->batteryDuration->text().toInt());
}

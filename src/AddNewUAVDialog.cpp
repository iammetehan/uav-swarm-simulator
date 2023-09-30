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

    ui->selectedColor->setAutoFillBackground(true);
    ui->selectedColor->setPalette(QPalette(Qt::red));

    ui->UAVModel->setText("New Model");

    connect(ui->selectImage, SIGNAL(clicked()), this, SLOT(SelectColor()));
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
                         ui->selectedColor->palette().color(QPalette::ColorRole::Button));
}

#include "ui_AddNewUAVDialog.h"
#include "AddNewUAVDialog.h"
#include "UAV.h"

AddNewUAVDialog::AddNewUAVDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewUAVDialog)
{
    ui->setupUi(this);

    connect(ui->OK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

AddNewUAVDialog::~AddNewUAVDialog()
{
    delete ui;
}

const Item::UAV AddNewUAVDialog::NewUAV()
{
    return Item::UAV(QImage(ui->selectedImage->text()),
                     ui->UAVModel->text(),
                     ui->UAVName->text());
}

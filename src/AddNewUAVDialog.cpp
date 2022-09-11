#include "AddNewUAVDialog.h"
#include "ui_AddNewUAVDialog.h"

AddNewUAVDialog::AddNewUAVDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewUAVDialog)
{
    ui->setupUi(this);
}

AddNewUAVDialog::~AddNewUAVDialog()
{
    delete ui;
}

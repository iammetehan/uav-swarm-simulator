#include "AddNewThreatDialog.h"
#include "ui_AddNewThreatDialog.h"

AddNewThreatDialog::AddNewThreatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewThreatDialog)
{
    ui->setupUi(this);
}

AddNewThreatDialog::~AddNewThreatDialog()
{
    delete ui;
}

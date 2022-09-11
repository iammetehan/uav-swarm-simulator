#include "ManageSwarmDialog.h"
#include "ui_ManageSwarmDialog.h"

ManageSwarmDialog::ManageSwarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageSwarmDialog)
{
    ui->setupUi(this);
}

ManageSwarmDialog::~ManageSwarmDialog()
{
    delete ui;
}

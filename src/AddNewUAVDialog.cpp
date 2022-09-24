#include "ui_AddNewUAVDialog.h"
#include "AddNewUAVDialog.h"
#include "UAV.h"
#include <QFileDialog>

AddNewUAVDialog::AddNewUAVDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewUAVDialog)
{
    ui->setupUi(this);

    connect(ui->selectImage, SIGNAL(clicked()), this, SLOT(SelectImage()));
    connect(ui->OK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

AddNewUAVDialog::~AddNewUAVDialog()
{
    delete ui;
}

void AddNewUAVDialog::SelectImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open File",
                                                    "D:/",
                                                    "Images (*.jpg *.png *.bmp )");
    ui->selectedImage->setText(fileName);
}


Item::UAV* AddNewUAVDialog::NewUAV()
{
    return new Item::UAV(ui->UAVModel->text(),
                     QImage(ui->selectedImage->text()));
}

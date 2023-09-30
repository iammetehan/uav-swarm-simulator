#include "SelectMapDialog.h"
#include "ui_SelectMapDialog.h"
#include <QRegularExpressionValidator>
#include <QFileDialog>

SelectMapDialog::SelectMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMapDialog)
{
    ui->setupUi(this);

    connect(ui->selectImage, SIGNAL(clicked()), this, SLOT(SelectImage()));
    connect(ui->OK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

SelectMapDialog::~SelectMapDialog()
{
    delete ui;
}

Data::Map SelectMapDialog::Map() const
{
    return Data::Map(ui->selectedImage->text());
}

void SelectMapDialog::SelectImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open File",
                                                    "D:/",
                                                    "Images (*.jpg *.png *.bmp )");
    ui->selectedImage->setText(fileName);
}

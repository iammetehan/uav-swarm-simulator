#include "SelectMapDialog.h"
#include "ui_SelectMapDialog.h"
#include <QRegularExpressionValidator>
#include <QFileDialog>

SelectMapDialog::SelectMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMapDialog)
{
    ui->setupUi(this);

    ui->leWidth->setValidator(Data::IntegerRegularExp());
    ui->leHeight->setValidator(Data::IntegerRegularExp());
    ui->leAltitude->setValidator(Data::IntegerRegularExp());

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
    return Data::Map(ui->leWidth->text().toInt(),
                     ui->leHeight->text().toInt(),
                     ui->leAltitude->text().toInt(),
                     ui->selectedImage->text());
}

void SelectMapDialog::SelectImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open File",
                                                    "D:/",
                                                    "Images (*.jpg *.png *.bmp )");
    ui->selectedImage->setText(fileName);
}

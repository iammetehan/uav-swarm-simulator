#include "ui_AddNewThreatDialog.h"
#include "AddNewThreatDialog.h"
#include <QColorDialog>
#include "Threat.h"

AddNewThreatDialog::AddNewThreatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewThreatDialog)
{
    ui->setupUi(this);

    ui->selectedColor->setAutoFillBackground(true);
    ui->selectedColor->setPalette(QPalette(Qt::red));

    ui->width->setValidator(Data::IntegerRegularExp());
    ui->height->setValidator(Data::IntegerRegularExp());

    connect(ui->selectColor, SIGNAL(clicked()), this, SLOT(SelectColor()));

    connect(ui->OK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

AddNewThreatDialog::~AddNewThreatDialog()
{
    delete ui;
}

const Item::Threat AddNewThreatDialog::NewThreat()
{
    return Item::Threat(ui->type->text(),
                        ui->width->text().toInt(),
                        ui->height->text().toInt(),
                        ui->selectedColor->palette().color(QPalette::ColorRole::Button));
}

void AddNewThreatDialog::SelectColor()
{
    ui->selectedColor->setPalette(QPalette(QColorDialog::getColor()));
}

#ifndef ADDNEWUAVDIALOG_H
#define ADDNEWUAVDIALOG_H

#include <QDialog>
#include "Definitions.h"

namespace Ui {
class AddNewUAVDialog;
}

class AddNewUAVDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewUAVDialog(QWidget *parent = nullptr);
    ~AddNewUAVDialog();

public:
    [[nodiscard]] Item::UAV* NewUAV();

private slots:
    void SelectColor();

private:
    Ui::AddNewUAVDialog *ui;
};

#endif // ADDNEWUAVDIALOG_H

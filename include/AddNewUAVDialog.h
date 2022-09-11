#ifndef ADDNEWUAVDIALOG_H
#define ADDNEWUAVDIALOG_H

#include <QDialog>

namespace Ui {
class AddNewUAVDialog;
}

class AddNewUAVDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewUAVDialog(QWidget *parent = nullptr);
    ~AddNewUAVDialog();

private:
    Ui::AddNewUAVDialog *ui;
};

#endif // ADDNEWUAVDIALOG_H

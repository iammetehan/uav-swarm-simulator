#ifndef ADDNEWTHREATDIALOG_H
#define ADDNEWTHREATDIALOG_H

#include <QDialog>

namespace Ui {
class AddNewThreatDialog;
}

class AddNewThreatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewThreatDialog(QWidget *parent = nullptr);
    ~AddNewThreatDialog();

private:
    Ui::AddNewThreatDialog *ui;
};

#endif // ADDNEWTHREATDIALOG_H

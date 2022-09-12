#ifndef ADDNEWTHREATDIALOG_H
#define ADDNEWTHREATDIALOG_H

#include <QDialog>
#include "Definitions.h"

namespace Ui {
class AddNewThreatDialog;
}

class AddNewThreatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewThreatDialog(QWidget *parent = nullptr);
    ~AddNewThreatDialog();

public:
    const Item::Threat NewThreat();

private slots:
    void SelectColor();

private:
    Ui::AddNewThreatDialog *ui;
};

#endif // ADDNEWTHREATDIALOG_H

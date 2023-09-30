#ifndef MANAGEMISSIONDIALOG_H
#define MANAGEMISSIONDIALOG_H

#include "Mission.h"

#include <QDialog>

namespace Ui {
class ManageMissionDialog;
}

class ManageMissionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageMissionDialog(QWidget *parent = nullptr);
    ~ManageMissionDialog();

    void SetDefaultMission(Item::Mission* mission);
private slots:
    void Accept();

private:
    Item::Mission* m_mission;

private:
    Ui::ManageMissionDialog *ui;
};

#endif // MANAGEMISSIONDIALOG_H

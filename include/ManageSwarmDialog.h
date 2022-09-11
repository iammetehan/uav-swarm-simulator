#ifndef MANAGESWARMDIALOG_H
#define MANAGESWARMDIALOG_H

#include <QDialog>

namespace Ui {
class ManageSwarmDialog;
}

class ManageSwarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageSwarmDialog(QWidget *parent = nullptr);
    ~ManageSwarmDialog();

private:
    Ui::ManageSwarmDialog *ui;
};

#endif // MANAGESWARMDIALOG_H

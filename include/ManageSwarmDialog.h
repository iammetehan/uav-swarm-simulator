#ifndef MANAGESWARMDIALOG_H
#define MANAGESWARMDIALOG_H

#include "UAV.h"
#include "Threat.h"
#include <QDialog>

namespace Ui {
class ManageSwarmDialog;
}

class ManageSwarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageSwarmDialog(const QList<Item::UAV *>& UAVModels,
                               const QList<Item::Threat *>& threats,
                               QWidget *parent = nullptr);
    ~ManageSwarmDialog();

private:
    void CreateSimItemWidgets();
    void CreateUAVModelWidgets();
    void CreateThreatTypeWidgets();
    QWidget *GetItemWidget(const QString &item);

public:
    QList<Item::UAV*> GetUAVs() const;
    QList<Item::Threat*> GetThreats() const;

private:
    const QList<Item::UAV *>& m_UAVModels;
    const QList<Item::Threat *>& m_threadTypes;

private:
    Ui::ManageSwarmDialog *ui;
};

#endif // MANAGESWARMDIALOG_H

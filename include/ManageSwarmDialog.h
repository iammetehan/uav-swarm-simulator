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

public:
    QList<Item::UAV*> GetUAVs() const;
    QList<Item::Threat*> GetThreats() const;

    // todo::iammetehan clone function can take a numOfItems as
    // parameter and returns the instances
    static QList<Item::UAV *> GetUAVInstances(const Item::UAV* uav,
                                              const int& numOfUAVs);

    static QList<Item::Threat *> GetThreatInstances(const Item::Threat* threat,
                                                    const int& numOfThreads);
private:
    void CreateSimItemWidgets();
    void CreateUAVModelWidgets();
    void CreateThreatTypeWidgets();
    QWidget *GetItemWidget(const QString &item);

private:
    const QList<Item::UAV *>& m_UAVModels;
    const QList<Item::Threat *>& m_threadTypes;

private:
    Ui::ManageSwarmDialog *ui;
};

#endif // MANAGESWARMDIALOG_H

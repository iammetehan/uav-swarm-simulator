#ifndef SIMITEM_H
#define SIMITEM_H

#include "Definitions.h"
#include <QGraphicsItem>

class Item::SimItem : public QGraphicsItem
{
public:
    SimItem(QGraphicsItem *parent = nullptr);
    SimItem(const QString& name,
            QGraphicsItem *parent = nullptr);
    virtual ~SimItem();

public:
    const QString &Name() const;
    void SetName(const QString& name);

public:
    virtual void Step();

protected:
    virtual SimItem* Clone(SimItem* simItem = nullptr) const;

private:
    QString m_name;
};

#endif // SIMITEM_H

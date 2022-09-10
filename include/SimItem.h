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

private:
    QString m_name;
};

#endif // SIMITEM_H

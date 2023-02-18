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
    virtual void BeforeSimulation();
    virtual void AfterSimulation();
    virtual void Step();
    virtual void ResetSimulation();

protected:
    virtual SimItem* Clone(SimItem* simItem = nullptr) const;

private:
    QString m_name;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SIMITEM_H

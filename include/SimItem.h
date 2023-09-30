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
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

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

protected:
    bool IsSimulationStarted() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool m_isSimulationStarted;
    QString m_name;
};

#endif // SIMITEM_H

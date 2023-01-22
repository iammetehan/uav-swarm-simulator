#ifndef UAV_H
#define UAV_H

#include "SimItem.h"

class Item::UAV : public SimItem
{

public:
    UAV(const QString& model = QString(),
        const QColor& m_color = QColor(Qt::black),
        const uint& speed = 0,
        const uint& batteryDuration = 0,
        QGraphicsItem *parent = nullptr);

public:
    QRectF boundingRect() const override;

public:
    Item::SimItem *Clone(SimItem *simItem = nullptr) const override;

public:
    void Step() override;

public:
    const QColor &Color() const;
    const QString &Model() const;

    const uint& Speed() const;
    const uint& BatteryDuration() const;

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    QColor m_color;
    QString m_model;
    uint m_speed;
    uint m_batteryDuration;

private:
    QVector<QPointF> path;


private:
    const qreal m_drawing_radius = 24;
};

#endif // UAV_H

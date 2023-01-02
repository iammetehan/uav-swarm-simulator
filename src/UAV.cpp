#include "UAV.h"
#include <QPainter>


Item::UAV::UAV(const QString &model,
               const QColor &color,
               const uint &speed,
               const uint &batteryDuration,
               QGraphicsItem *parent)
    : SimItem(parent),
      m_color(color),
      m_model(model),
      m_speed(speed),
      m_batteryDuration(batteryDuration)
{

}

QRectF Item::UAV::boundingRect() const
{
    qreal halfOfWidth = m_radius / 2;
    qreal halfOfHeight = m_radius / 2;


    return QRectF(-halfOfWidth,
                  -halfOfHeight,
                  halfOfWidth,
                  halfOfHeight);
}

Item::SimItem *Item::UAV::Clone(SimItem* simItem) const
{
    return SimItem::Clone(new UAV(Model(),
                                  Color(),
                                  Speed(),
                                  BatteryDuration()));
}

void Item::UAV::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{

    painter->setOpacity(0.8);
    painter->setBrush(m_color);
    painter->drawEllipse(boundingRect());

}


const QString &Item::UAV::Model() const
{
    return m_model;
}

const QColor &Item::UAV::Color() const
{
    return m_color;
}

const uint &Item::UAV::Speed() const
{
    return m_speed;
}

const uint &Item::UAV::BatteryDuration() const
{
    return m_batteryDuration;
}

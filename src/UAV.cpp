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
    qreal halfOfWidth = m_drawing_radius / 2;
    qreal halfOfHeight = m_drawing_radius / 2;


    return QRectF(-halfOfWidth,
                  -halfOfHeight,
                  m_drawing_radius,
                  m_drawing_radius);
}

Item::SimItem *Item::UAV::Clone(SimItem* simItem) const
{
    return SimItem::Clone(new UAV(Model(),
                                  Color(),
                                  Speed(),
                                  BatteryDuration()));
}

void Item::UAV::Step()
{
    if (!arrived)
    {
        setPos(NextPos());
    }
}

void Item::UAV::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    painter->setBrush(m_color);
    painter->setOpacity(0.8);
    painter->drawEllipse(boundingRect());

    if (arrived)
    {
        painter->drawText(QPointF(0,0), "Arrived!");
    }
}

QPointF Item::UAV::NextPos()
{
    QPointF nextPos = pos() + AddLengthToPoint(stepSize,
                                               AngleBtwPoints(pos(), NextPoint()));
    QRectF area(pos(), nextPos);

    if (area.contains(NextPoint()))
    {
        if (NextPoint() == path.last())
        {
            arrived = true;
            nextPos = path.last();
        }
        else
        {
            qreal nStepSize = stepSize - LengthBtwPoints(pos(), NextPoint());
            QPointF currPoint = NextPoint();
            nextPointIndex++;
            nextPos = currPoint + AddLengthToPoint(nStepSize,
                                                     AngleBtwPoints(currPoint, NextPoint()));
        }
    }

    return nextPos;
}

const QPointF &Item::UAV::NextPoint() const
{
    return path.at(nextPointIndex);
}

QPointF Item::UAV::AddLengthToPoint(const qreal& length, const qreal& angle) const
{
    QLineF line(QPointF(0,0), QPointF(1,1));
    line.setLength(length);
    line.setAngle(angle);
    return line.p2();
}

qreal Item::UAV::AngleBtwPoints(const QPointF &p1, const QPointF &p2) const
{
    return QLineF(p1, p2).angle();
}

qreal Item::UAV::LengthBtwPoints(const QPointF &p1, const QPointF &p2) const
{
    return QLineF(p1, p2).length();
}

const QVector<QPointF> &Item::UAV::GetPath() const
{
    return path;
}

void Item::UAV::SetPath(const QVector<QPointF> &newPath)
{
    path = newPath;
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

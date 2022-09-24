#include "Threat.h"
#include <QPainter>

Item::Threat::Threat(const QString &type,
                     const qreal &width,
                     const qreal &height,
                     const QColor &color,
                     QGraphicsItem *parent)
    : SimItem(parent),
      m_type(type),
      m_width(width),
      m_height(height),
      m_color(color)
{

}

QRectF Item::Threat::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void Item::Threat::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setOpacity(0.3);
    painter->setBrush(m_color);
    painter->drawEllipse(boundingRect());
}

Item::SimItem *Item::Threat::Clone(SimItem *simItem) const
{
    return SimItem::Clone(new Threat(Type(),
                                     Width(),
                                     Height(),
                                     Color()));
}

const QColor &Item::Threat::Color() const
{
    return m_color;
}

qreal Item::Threat::Height() const
{
    return m_height;
}

qreal Item::Threat::Width() const
{
    return m_width;
}

const QString &Item::Threat::Type() const
{
    return m_type;
}


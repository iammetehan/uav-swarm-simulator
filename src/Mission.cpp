#include "Mission.h"
#include <QPainter>

Item::Mission::Mission(const QString &type,
                     const qreal &width,
                     const qreal &height,
                     QGraphicsItem *parent)
    : SimItem("Mission: " + type, parent),
      m_type(type),
      m_width(width),
      m_height(height),
      m_color(Qt::GlobalColor::cyan)
{

}

QRectF Item::Mission::boundingRect() const
{
    qreal halfOfWidth = m_width / 2;
    qreal halfOfHeight = m_height / 2;

    return QRectF(QPointF(-halfOfWidth, -halfOfHeight),
                  QPointF(halfOfWidth, halfOfHeight));
}

void Item::Mission::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SimItem::paint(painter, option, widget);

    painter->setOpacity(0.3);
    painter->setBrush(m_color);
    painter->drawRect(boundingRect());
}

Item::SimItem *Item::Mission::Clone(SimItem *simItem) const
{
    return SimItem::Clone(new Mission(Type(),
                                     Width(),
                                     Height()));
}

const QColor &Item::Mission::Color() const
{
    return m_color;
}

void Item::Mission::SetType(const QString &newType)
{
    m_type = newType;
}

void Item::Mission::SetHeight(qreal newHeight)
{
    m_height = newHeight;
}

void Item::Mission::SetWidth(qreal newWidth)
{
    m_width = newWidth;
}

qreal Item::Mission::Height() const
{
    return m_height;
}

qreal Item::Mission::Width() const
{
    return m_width;
}

const QString &Item::Mission::Type() const
{
    return m_type;
}


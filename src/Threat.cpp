#include "Threat.h"
#include <QPainter>

Item::Threat::Threat(const int &width,
                     const int &height,
                     const QColor &color,
                     QGraphicsItem *parent)
    : SimItem(parent),
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
    painter->setBrush(m_color);
    painter->drawEllipse(boundingRect());
}


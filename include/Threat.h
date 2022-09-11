#ifndef THREAT_H
#define THREAT_H

#include "SimItem.h"
#include <QColor>

class Item::Threat : public SimItem
{
public:
    Threat(const int& width,
           const int& height,
           const QColor& color,
           QGraphicsItem *parent = nullptr);


public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal m_width;
    qreal m_height;
    QColor m_color;
};

#endif // THREAT_H

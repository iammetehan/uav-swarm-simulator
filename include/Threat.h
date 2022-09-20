#ifndef THREAT_H
#define THREAT_H

#include "SimItem.h"
#include <QColor>

class Item::Threat : public SimItem
{
public:
    Threat(const QString& type = QString(),
           const qreal& width = 0.0,
           const qreal& height = 0.0,
           const QColor& color = QColor(Qt::black),
           QGraphicsItem *parent = nullptr);

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    const QString &Type() const;
    qreal Width() const;
    qreal Height() const;
    const QColor &Color() const;

private:
    QString m_type;
    qreal m_width;
    qreal m_height;
    QColor m_color;
};

#endif // THREAT_H

#ifndef MISSION_H
#define MISSION_H

#include "SimItem.h"
#include <QColor>

class Item::Mission : public SimItem
{
public:
    Mission(const QString& type = QString(),
           const qreal& width = 0.0,
           const qreal& height = 0.0,
           QGraphicsItem *parent = nullptr);

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

public:
    Item::SimItem *Clone(SimItem *simItem = nullptr) const override;

public:
    void SetWidth(qreal newWidth);
    void SetHeight(qreal newHeight);
    void SetType(const QString &newType);

    const QString &Type() const;
    qreal Width() const;
    qreal Height() const;
    const QColor &Color() const;

private:
    QString m_type;
    qreal m_width;
    qreal m_height;
    const QColor m_color;
};

#endif // MISSION_H

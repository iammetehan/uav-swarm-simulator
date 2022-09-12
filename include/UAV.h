#ifndef UAV_H
#define UAV_H

#include "SimItem.h"

class Item::UAV : public SimItem
{

public:
    UAV(const QImage& image,
        const QString& model,
        const QString& name,
        QGraphicsItem *parent = nullptr);

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QImage m_image;
    QString m_model;
};

#endif // UAV_H

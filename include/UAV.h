#ifndef UAV_H
#define UAV_H

#include "SimItem.h"

class Item::UAV : public SimItem
{

public:
    UAV(const QString& model = QString(),
        const QImage& image = QImage(),
        QGraphicsItem *parent = nullptr);

public:
    QRectF boundingRect() const;

public:
    const QImage &Image() const;
    const QString &Model() const;

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QImage m_image;
    QString m_model;
};

#endif // UAV_H

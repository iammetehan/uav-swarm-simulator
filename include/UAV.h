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
    QRectF boundingRect() const override;

public:
    Item::SimItem *Clone(SimItem *simItem = nullptr) const override;

public:
    const QImage &Image() const;
    const QString &Model() const;

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    QImage m_image;
    QString m_model;
};

#endif // UAV_H

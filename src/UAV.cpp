#include "UAV.h"
#include <QPainter>


Item::UAV::UAV(const QImage &image,
               const QString &model,
               const QString &name,
               QGraphicsItem *parent)
    : SimItem(name, parent), m_model(model)
{
    m_image = image.scaled(Item::UAVImageSize(),
                           Qt::AspectRatioMode::KeepAspectRatio);
}

QRectF Item::UAV::boundingRect() const
{
    return QRectF(m_image.rect());
}

void Item::UAV::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    painter->drawImage(m_image.rect(), m_image);
}

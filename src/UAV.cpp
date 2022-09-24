#include "UAV.h"
#include <QPainter>


Item::UAV::UAV(const QString &model,
               const QImage &image,
               QGraphicsItem *parent)
    : SimItem(parent),
      m_model(model)
{
    m_image = image.scaled(Item::UAVImageSize(),
                           Qt::AspectRatioMode::KeepAspectRatio);
}

QRectF Item::UAV::boundingRect() const
{
    return QRectF(m_image.rect());
}

Item::SimItem *Item::UAV::Clone(SimItem* simItem) const
{
    return SimItem::Clone(new UAV(Model(),
                                  Image()));
}

void Item::UAV::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    painter->drawImage(m_image.rect(), m_image);
}

const QString &Item::UAV::Model() const
{
    return m_model;
}

const QImage &Item::UAV::Image() const
{
    return m_image;
}

#include "Definitions.h"
#include "qpainter.h"

Data::Map::Map()
{

}

Data::Map::Map(const std::size_t w, const std::size_t h,
               const std::size_t a, const QString imgPath) :
    m_w(w), m_h(h), m_a(a)
{
    m_image = QImage(imgPath);
}

std::size_t Data::Map::W() const
{
    return m_w;
}

std::size_t Data::Map::H() const
{
    return m_h;
}

std::size_t Data::Map::A() const
{
    return m_a;
}

const QImage &Data::Map::Image() const
{
    return m_image;
}

Item::SimItem::SimItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

Item::SimItem::SimItem(const QString &name, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_name(name)
{

}

Item::SimItem::~SimItem()
{

}

const QString &Item::SimItem::Name() const
{
    return m_name;
}

Item::UAV::UAV(const QImage &image, const QString &name, QGraphicsItem *parent)
    : SimItem(name, parent)
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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstddef>
#include <QImage>
#include <QGraphicsItem>

namespace Data
{
    class Map;
}

class Data::Map
{
public:
    Map();
    Map(const std::size_t w,
        const std::size_t h,
        const std::size_t a,
        const QString imgPath);

public:
    std::size_t W() const;
    std::size_t H() const;
    std::size_t A() const;
    const QImage &Image() const;

private:
    std::size_t m_w;
    std::size_t m_h;
    std::size_t m_a;
    QImage m_image;
};


namespace Item
{
    class SimItem;
    class UAV;
    constexpr QSize UAVImageSize() {return QSize(24, 24);};
}

class Item::SimItem : public QGraphicsItem
{
public:
    SimItem(QGraphicsItem *parent = nullptr);
    SimItem(const QString& name,
            QGraphicsItem *parent = nullptr);
    virtual ~SimItem();

public:
    const QString &Name() const;

private:
    QString m_name;
};

class Item::UAV : public SimItem
{

public:
    UAV(const QImage& image,
        const QString& name,
        QGraphicsItem *parent = nullptr);

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QImage m_image;

};


#endif // DEFINITIONS_H

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstddef>
#include <QImage>
#include <QGraphicsItem>

namespace Data
{
    class Map
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
}

namespace Item
{
    class SimItem;
    class UAV;
    class Threat;
    constexpr QSize UAVImageSize() {return QSize(24, 24);};
}

#endif // DEFINITIONS_H

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstddef>
#include <QImage>
#include <QGraphicsItem>
#include <QValidator>

namespace Data
{
    [[nodiscard]] QRegularExpressionValidator* IntegerRegularExp();

    class Map
    {
    public:
        Map();
        Map(const std::size_t w,
            const std::size_t h,
            const std::size_t a,
            const QString imgPath);

    public:
        static constexpr std::size_t TotalNumOfPoints(){ return HNumOfPoints() * WNumOfPoints(); }
        static constexpr std::size_t HNumOfPoints(){ return 10; }
        static constexpr std::size_t WNumOfPoints(){ return 16; }
        static constexpr qreal PointRadius(){ return 5.0; }

    public:
        std::size_t W() const;
        std::size_t H() const;
        std::size_t A() const;
        const QImage &Image() const;
        const QVector<QPointF> &Points() const;
        QVector<QVector<QPointF>> IndexesToPaths(QVector<QVector<int>> indexes) const;
        QVector<QPointF> IndexesToPath(QVector<int> indexes) const;

    private:
        std::size_t m_w;
        std::size_t m_h;
        std::size_t m_a;
        QImage m_image;
        QVector<QPointF> points;
    };
}

namespace Item
{
    class SimItem;
    class UAV;
    class Threat;

    constexpr QRectF SceneRect() {return QRectF(QPointF(-5000, -5000),
                                                QPointF(5000, 5000));};
    constexpr uint8_t MinNumOfItem() {return 1;};
    constexpr uint8_t MaxNumOfItem() {return 32;};

}

#endif // DEFINITIONS_H

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
        Map(const QString imgPath);

    public:
        static constexpr std::size_t TotalNumOfPoints(){ return HNumOfPoints() * WNumOfPoints(); }
        static constexpr std::size_t HNumOfPoints(){ return 10; }
        static constexpr std::size_t WNumOfPoints(){ return 16; }
        static constexpr qreal PointRadius(){ return 5.0; }

    public:
        const QImage& Image() const;
        const QVector<QPointF>& Points() const;
        QVector<QVector<QPointF>> IndexesToPaths(QVector<QVector<int>> indexes) const;
        QVector<QPointF> IndexesToPath(QVector<int> indexes) const;

    private:
        QImage m_image;
        QVector<QPointF> m_points;
    };
}

namespace Item
{
    class SimItem;
    class UAV;
    class Threat;
    class Mission;

    constexpr QRectF SceneRect() {return QRectF(QPointF(-5000, -5000),
                                                QPointF(5000, 5000));};
    constexpr uint8_t MinNumOfItem() {return 1;};
    constexpr uint8_t MaxNumOfItem() {return 32;};

    constexpr QLatin1String Surveillance() {return QLatin1String("Surveillance"); };
    constexpr QLatin1String Reconnaissance() {return QLatin1String("Reconnaissance"); };
    [[nodiscard]] QStringList MissionTypes();
}

#endif // DEFINITIONS_H

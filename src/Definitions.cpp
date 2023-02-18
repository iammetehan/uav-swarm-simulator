#include "Definitions.h"

Data::Map::Map()
{

}

Data::Map::Map(const std::size_t w, const std::size_t h,
               const std::size_t a, const QString imgPath) :
    m_w(w), m_h(h), m_a(a)
{
    m_image = QImage(imgPath);

    qreal widthOffset = m_image.width() / static_cast<double>(WNumOfPoints() - 1);
    qreal heightOffset = m_image.height() / static_cast<double>(HNumOfPoints() - 1);

    for (int i = 0; i < WNumOfPoints(); i++)
    {
        for (int k = 0; k < HNumOfPoints(); k++)
        {
            points.append(QPointF(i * widthOffset,
                                  k * heightOffset));
        }
    }

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

const QVector<QPointF> &Data::Map::Points() const
{
    return points;
}

QVector<QVector<QPointF> > Data::Map::IndexesToPaths(QVector<QVector<int> > indexes) const
{
    QVector<QVector<QPointF>> paths;
    for (const QVector<int>& pathIndexes: indexes)
    {
        paths.append(IndexesToPath(pathIndexes));
    }

    return paths;
}

QVector<QPointF> Data::Map::IndexesToPath(QVector<int> indexes) const
{
    QVector<QPointF> points;
    for (const int& i: indexes)
    {
        points.append(this->points.at(i));
    }

    return points;
}


QRegularExpressionValidator *Data::IntegerRegularExp()
{
    return new QRegularExpressionValidator(QRegularExpression("[0-9]*"));
}

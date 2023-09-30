#include "Definitions.h"

Data::Map::Map()
{

}

Data::Map::Map(const QString imgPath)
{
    m_image = QImage(imgPath);

    qreal widthOffset = m_image.width() / static_cast<double>(WNumOfPoints() - 1);
    qreal heightOffset = m_image.height() / static_cast<double>(HNumOfPoints() - 1);

    for (int i = 0; i < WNumOfPoints(); i++)
    {
        for (int k = 0; k < HNumOfPoints(); k++)
        {
            m_points.append(QPointF(i * widthOffset,
                                  k * heightOffset));
        }
    }

}

const QImage &Data::Map::Image() const
{
    return m_image;
}

const QVector<QPointF> &Data::Map::Points() const
{
    return m_points;
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
        points.append(this->m_points.at(i));
    }

    return points;
}


QRegularExpressionValidator *Data::IntegerRegularExp()
{
    return new QRegularExpressionValidator(QRegularExpression("[0-9]*"));
}

QStringList Item::MissionTypes()
{
    return QStringList({Surveillance(), Reconnaissance()});
}

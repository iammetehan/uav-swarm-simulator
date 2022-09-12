#include "Definitions.h"

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

QRegularExpressionValidator *Data::IntegerRegularExp()
{
    return new QRegularExpressionValidator(QRegularExpression("[0-9]*"));
}

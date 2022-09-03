#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstddef>
#include <QImage>

namespace Data
{
    class Map
    {
    public:
        Map() {}
        Map(const std::size_t w,
            const std::size_t h,
            const std::size_t a,
            const QString imgPath) :
            m_w(w), m_h(h), m_a(a)
        {
            m_Image = QImage(imgPath);
        }

    public:
        std::size_t W() const
        {
            return m_w;
        }
        std::size_t H() const
        {
            return m_h;
        }
        std::size_t A() const
        {
            return m_a;
        }
        const QImage &Image() const
        {
            return m_Image;
        }

    private:
        std::size_t m_w;
        std::size_t m_h;
        std::size_t m_a;
        QImage m_Image;
    };
}



#endif // DEFINITIONS_H

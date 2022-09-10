#include "SimItem.h"

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

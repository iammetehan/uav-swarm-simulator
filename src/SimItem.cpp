#include "SimItem.h"

Item::SimItem::SimItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

Item::SimItem::SimItem(const QString &name, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_name(name)
{

}

Item::SimItem::~SimItem()
{

}

Item::SimItem *Item::SimItem::Clone(SimItem *simItem) const
{
    if (nullptr != simItem)
    {
        simItem->SetName(Name());
        return simItem;
    }
    return nullptr;
}

const QString &Item::SimItem::Name() const
{
    return m_name;
}

void Item::SimItem::SetName(const QString &name)
{
    m_name = name;
}

void Item::SimItem::Step()
{
    // meteaydn: make the function pure
}

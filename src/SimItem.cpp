#include "SimItem.h"
#include <QPainter>
#include <QGraphicsScene>

Item::SimItem::SimItem(QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_isSimulationStarted(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

Item::SimItem::SimItem(const QString &name, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_name(name),
      m_isSimulationStarted(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

Item::SimItem::~SimItem()
{

}

void Item::SimItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(Qt::white);
    QFont font = painter->font();
    font.setPointSize(10);

    painter->setPen(pen);
    painter->setFont(font);

    QTextOption options;
    options.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QPointF topLeft(-100, -8);
    QPointF bottomRight(100, 8);

    QRectF rect(topLeft, bottomRight);

    QPointF topCenter(boundingRect().center().x(), boundingRect().top() - 8);

    rect.moveCenter(topCenter);

    painter->drawText(rect, m_name, options);
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

bool Item::SimItem::IsSimulationStarted() const
{
    return m_isSimulationStarted;
}

void Item::SimItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    scene()->invalidate(Item::SceneRect());
}

void Item::SimItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    scene()->invalidate(Item::SceneRect());
}

void Item::SimItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    scene()->invalidate(Item::SceneRect());
}

const QString &Item::SimItem::Name() const
{
    return m_name;
}

void Item::SimItem::SetName(const QString &name)
{
    m_name = name;
}

void Item::SimItem::BeforeSimulation()
{
    // meteaydn: make the function pure
    m_isSimulationStarted = true;
}

void Item::SimItem::AfterSimulation()
{
    // meteaydn: make the function pure
    m_isSimulationStarted = false;

}

void Item::SimItem::Step()
{
    // meteaydn: make the function pure
}

void Item::SimItem::ResetSimulation()
{
    // meteaydn: make the function pure
}

#include "Scene.h"
#include "Definitions.h"

Display::Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{
    setSceneRect(Item::SceneRect());
}

const Data::Map &Display::Scene::Map() const
{
    return m_map;
}

void Display::Scene::SetMap(const Data::Map &newMap)
{
    m_map = newMap;
}

void Display::Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    using namespace Data;

    painter->drawImage(m_map.Image().rect(), m_map.Image());
    painter->setBrush(Qt::blue);

    for (const QPointF& point : m_map.Points())
    {
        painter->drawEllipse(point, Map::PointRadius(), Map::PointRadius());
    }
}

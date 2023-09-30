#include "Scene.h"
#include "Definitions.h"
#include <UAV.h>

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
    using namespace Item;

    painter->drawImage(m_map.Image().rect(), m_map.Image());

#ifdef SHOWMAPPOINTS
    painter->setBrush(Qt::blue);
    for (const QPointF& point : m_map.Points())
    {
        painter->drawEllipse(point, Map::PointRadius(), Map::PointRadius());
    }
#endif

    for(QGraphicsItem* item: items())
    {
        UAV* uav = dynamic_cast<UAV*>(item);

        if (nullptr != uav)
        {
            if (uav->ShowCurrentPath())
            {
                QPen pen;
                pen.setBrush(uav->Color());
                pen.setWidth(3);

                painter->setPen(pen);
                painter->setBrush(Qt::transparent);

                painter->drawPath(uav->Lines());
            }
        }
    }

}

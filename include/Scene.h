#ifndef SCENE_H
#define SCENE_H

#include "Definitions.h"
#include <QGraphicsScene>
#include <QPainter>

namespace Display
{
    class Scene;
}

class Display::Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);


public:
    const Data::Map &Map() const;
    void SetMap(const Data::Map &newMap);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    Data::Map m_map;

};

#endif // SCENE_H

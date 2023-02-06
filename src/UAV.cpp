#include "UAV.h"
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include <QGraphicsView>


Item::UAV::UAV(const QString &model,
               const QColor &color,
               const uint &speed,
               const uint &batteryDuration,
               QGraphicsItem *parent)
    : SimItem(parent),
      m_color(color),
      m_model(model),
      m_speed(speed),
      m_batteryDuration(batteryDuration)
{

}

QRectF Item::UAV::boundingRect() const
{
    if (showCurrentPath)
    {
        return ItemBRect().united(Lines().boundingRect());
    }

    return ItemBRect();
}

QPainterPath Item::UAV::shape() const
{
    QPainterPath path;
    path.addRect(ItemBRect());

    return path;
}

Item::SimItem *Item::UAV::Clone(SimItem* simItem) const
{
    return SimItem::Clone(new UAV(Model(),
                                  Color(),
                                  Speed(),
                                  BatteryDuration()));
}

void Item::UAV::Step()
{
    if (!arrived)
    {
        setPos(NextPos());
    }
}

void Item::UAV::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    painter->setBrush(m_color);
    painter->setOpacity(0.8);
    painter->drawEllipse(ItemBRect());

    if (arrived)
    {
        painter->drawText(QPointF(0,0), "Arrived!");
    }

    if (showCurrentPath)
    {
        QPen pen;
        pen.setBrush(m_color);
        pen.setWidth(3);

        painter->setPen(pen);
        painter->setBrush(Qt::transparent);

        painter->drawPath(Lines());
    }
}

QRectF Item::UAV::ItemBRect() const
{
    qreal halfOfWidth = m_drawing_radius / 2;
    qreal halfOfHeight = m_drawing_radius / 2;


    return QRectF(-halfOfWidth,
                  -halfOfHeight,
                  m_drawing_radius,
                  m_drawing_radius);
}

QPainterPath Item::UAV::Lines() const
{
    QPainterPath lines;
    lines.moveTo(QPointF(0, 0));
    for(const QPointF& p: CurrentPath())
    {
        lines.lineTo(mapFromScene(p));
    }

    return lines;
}

QPointF Item::UAV::NextPos()
{
    QPointF nextPos = pos() + AddLengthToPoint(stepSize,
                                               AngleBtwPoints(pos(), NextPoint()));
    QRectF area(pos(), nextPos);

    if (area.contains(NextPoint()))
    {
        if (NextPoint() == CurrentPath().last())
        {
            arrived = true;
            nextPos = CurrentPath().last();
        }
        else
        {
            qreal nStepSize = stepSize - LengthBtwPoints(pos(), NextPoint());
            QPointF currPoint = NextPoint();
            nextPointIndex++;
            nextPos = currPoint + AddLengthToPoint(nStepSize,
                                                     AngleBtwPoints(currPoint, NextPoint()));
        }
    }

    return nextPos;
}

const QPointF &Item::UAV::NextPoint() const
{
    return CurrentPath().at(nextPointIndex);
}

QPointF Item::UAV::AddLengthToPoint(const qreal& length, const qreal& angle) const
{
    QLineF line(QPointF(0,0), QPointF(1,1));
    line.setLength(length);
    line.setAngle(angle);
    return line.p2();
}

qreal Item::UAV::AngleBtwPoints(const QPointF &p1, const QPointF &p2) const
{
    return QLineF(p1, p2).angle();
}

qreal Item::UAV::LengthBtwPoints(const QPointF &p1, const QPointF &p2) const
{
    return QLineF(p1, p2).length();
}

const QVector<QVector<QPointF> > &Item::UAV::GetPaths() const
{
    return paths;
}

void Item::UAV::SetPaths(const QVector<QVector<QPointF>> &newPaths)
{
    paths = newPaths;
}

const QVector<QPointF> &Item::UAV::CurrentPath() const
{
    if (currentPathIndex < paths.size())
    {
        return paths.at(currentPathIndex);
    }
    return defaultPath;
}

const QString &Item::UAV::Model() const
{
    return m_model;
}

const QColor &Item::UAV::Color() const
{
    return m_color;
}

const uint &Item::UAV::Speed() const
{
    return m_speed;
}

const uint &Item::UAV::BatteryDuration() const
{
    return m_batteryDuration;
}

void Item::UAV::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QVector<QAction*> actions;
    QMenu menu;

    for(int i = 0; i < paths.size(); i++)
    {
        QAction *action = new QAction("Path " + QString::number(i + 1));
        action->setCheckable(true);

        actions.append(action);
        menu.addAction(action);

        if (currentPathIndex == i)
        {
            action->setChecked(Qt::Checked);
        }
        else
        {
            action->setChecked(Qt::Unchecked);
        }
    }

    QAction *showCurrPath = new QAction("Show Current Path");
    showCurrPath->setCheckable(true);
    menu.addAction(showCurrPath);

    if (showCurrentPath)
    {
        showCurrPath->setChecked(Qt::Checked);
    }
    else
    {
        showCurrPath->setChecked(Qt::Unchecked);
    }

    QAction *a = menu.exec(event->screenPos());

    if (nullptr != a)
    {
        if (showCurrPath == a)
        {
            if (showCurrentPath)
            {
                showCurrentPath = false;
            }
            else
            {
                showCurrentPath = true;
            }
        }
        else
        {
            currentPathIndex = actions.indexOf(a);
            qDebug() << "Selected path :" << a->text();
        }
        scene()->invalidate(Item::SceneRect());
    }

    for(QAction* action: actions)
    {
        delete action;
    }
    delete showCurrPath;
}

#include "UAV.h"
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include <QGraphicsView>


Item::UAV::UAV(const QString &model,
               const QColor &color,
               QGraphicsItem *parent)
    : SimItem(parent),
      m_color(color),
      m_model(model)
{

}

QRectF Item::UAV::boundingRect() const
{
    return ItemBRect();
}

Item::SimItem *Item::UAV::Clone(SimItem* simItem) const
{
    return SimItem::Clone(new UAV(Model(),
                                  Color()));
}

void Item::UAV::Step()
{
    SimItem::Step();

    if (!m_arrived)
    {
        setPos(NextPos());
    }
}

void Item::UAV::ResetSimulation()
{
    SimItem::ResetSimulation();

    m_arrived = false;
    m_nextPointIndex = 0;
}

void Item::UAV::BeforeSimulation()
{
    SimItem::BeforeSimulation();
    ResetSimulation();
    m_firstSource = Source();
}

void Item::UAV::AfterSimulation()
{
    SimItem::AfterSimulation();
    ResetSimulation();
}

void Item::UAV::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    SimItem::paint(painter, option, widget);

    painter->setBrush(m_color);
    painter->setOpacity(0.8);
    painter->drawEllipse(ItemBRect());

    if (m_arrived)
    {
        painter->drawText(QPointF(0,0), "Completed!");
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

    if (IsSimulationStarted())
    {
        lines.moveTo(m_firstSource);
    }
    else
    {
        lines.moveTo(Source());
    }

    for(const QPointF& p: CurrentPath())
    {
        lines.lineTo(p);
    }

    return lines;
}

QPointF Item::UAV::NextPos()
{
    QPointF nextPos = pos() + AddLengthToPoint(m_stepSize,
                                               AngleBtwPoints(pos(), NextPoint()));
    QRectF area(pos(), nextPos);

    if (0 == area.width())
    {
        area.setWidth(1);
    }

    if (0 == area.height())
    {
        area.setHeight(1);
    }

    if (area.contains(NextPoint()))
    {
        if (NextPoint() == CurrentPath().last())
        {
            m_arrived = true;
            nextPos = CurrentPath().last();
        }
        else
        {
            qreal nStepSize = m_stepSize - LengthBtwPoints(pos(), NextPoint());
            QPointF currPoint = NextPoint();
            m_nextPointIndex++;
            nextPos = currPoint + AddLengthToPoint(nStepSize,
                                                     AngleBtwPoints(currPoint, NextPoint()));
        }
    }

    return nextPos;
}

const QPointF &Item::UAV::NextPoint() const
{
    return CurrentPath().at(m_nextPointIndex);
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

bool Item::UAV::IsArrived() const
{
    return m_arrived;
}

bool Item::UAV::ShowCurrentPath() const
{
    return m_showCurrentPath;
}

QPointF Item::UAV::Source() const
{
    return pos();
}

QPointF Item::UAV::Destination() const
{
    return m_destination;
}

void Item::UAV::SetDestination(const QPointF& destination)
{
    m_destination = destination;
}

const QVector<QVector<QPointF> > &Item::UAV::GetPaths() const
{
    return m_paths;
}

void Item::UAV::SetPaths(const QVector<QVector<QPointF>> &newPaths)
{
    m_paths = newPaths;
}

QVector<QPointF> Item::UAV::CurrentPath() const
{
    if (m_currentPathIndex < m_paths.size())
    {
        QVector<QPointF> path = m_paths.at(m_currentPathIndex);
        path.append(Destination());
        return path;
    }
    return m_defaultPath;
}

QVector<QPointF> Item::UAV::FullPath() const
{
    QVector<QPointF> fPath;
    fPath.append(Source());
    fPath.append(CurrentPath());
    return fPath;
}

const QString &Item::UAV::Model() const
{
    return m_model;
}

const QColor &Item::UAV::Color() const
{
    return m_color;
}

void Item::UAV::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QVector<QAction*> actions;
    QMenu menu;

    for(int i = 0; i < m_paths.size(); i++)
    {
        QAction *action = new QAction("Path " + QString::number(i + 1));
        action->setCheckable(true);

        actions.append(action);
        menu.addAction(action);

        if (m_currentPathIndex == i)
        {
            action->setChecked(Qt::Checked);
        }
        else
        {
            action->setChecked(Qt::Unchecked);
        }
    }

    QAction *showCurrPathAction = new QAction("Show Current Path");
    showCurrPathAction->setCheckable(true);
    menu.addAction(showCurrPathAction);

    if (m_showCurrentPath)
    {
        showCurrPathAction->setChecked(Qt::Checked);
    }
    else
    {
        showCurrPathAction->setChecked(Qt::Unchecked);
    }

    QAction *a = menu.exec(event->screenPos());

    if (nullptr != a)
    {
        if (showCurrPathAction == a)
        {
            m_showCurrentPath = !m_showCurrentPath;
        }
        else
        {
            m_currentPathIndex = actions.indexOf(a);
            qDebug() << "Selected path :" << a->text();
        }
        scene()->invalidate(Item::SceneRect());
    }

    for(QAction* action: actions)
    {
        delete action;
    }

    delete showCurrPathAction;
}

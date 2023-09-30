#ifndef UAV_H
#define UAV_H

#include "SimItem.h"

class Item::UAV : public SimItem
{

public:
    UAV(const QString& model = QString(),
        const QColor& m_color = QColor(Qt::black),
        QGraphicsItem *parent = nullptr);

public:
    QRectF boundingRect() const override;

public:
    Item::SimItem *Clone(SimItem *simItem = nullptr) const override;

public:
    void Step() override;
    void ResetSimulation() override;

    void BeforeSimulation() override;
    void AfterSimulation() override;

public:
    const QColor &Color() const;
    const QString &Model() const;

    const QVector<QVector<QPointF>> &GetPaths() const;
    void SetPaths(const QVector<QVector<QPointF>> &newPaths);

    QVector<QPointF> CurrentPath() const;
    QVector<QPointF> FullPath() const;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    QPointF Source() const;
    void SetDestination(const QPointF& destination);
    QPointF Destination() const;

    bool ShowCurrentPath() const;
    QPainterPath Lines() const;

    bool IsArrived() const;

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    QRectF ItemBRect() const;

private:
    QPointF NextPos();

private:
    const QPointF &NextPoint() const;

private:
    QPointF AddLengthToPoint(const qreal& length, const qreal &angle) const;
    qreal AngleBtwPoints(const QPointF& p1, const QPointF& p2) const;
    qreal LengthBtwPoints(const QPointF& p1, const QPointF& p2) const;

private:
    bool m_arrived = false;

private:
    qreal m_stepSize = 2; // px
    int m_nextPointIndex = 0;

private:
    QColor m_color;
    QString m_model;

private:
    bool m_showCurrentPath = false;
    std::size_t m_currentPathIndex = 0;
    QVector<QPointF> m_defaultPath;
    QPointF m_firstSource;
    QVector<QVector<QPointF>> m_paths;
    QPointF m_destination;

private:
    const qreal m_drawing_radius = 24;
};

#endif // UAV_H

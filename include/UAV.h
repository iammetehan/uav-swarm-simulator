#ifndef UAV_H
#define UAV_H

#include "SimItem.h"

class Item::UAV : public SimItem
{

public:
    UAV(const QString& model = QString(),
        const QColor& m_color = QColor(Qt::black),
        const uint& speed = 0,
        const uint& batteryDuration = 0,
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

    const uint& Speed() const;
    const uint& BatteryDuration() const;

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
    bool arrived = false;

private:
    qreal stepSize = 2; // px
    int nextPointIndex = 0;

private:
    QColor m_color;
    QString m_model;
    uint m_speed;
    uint m_batteryDuration;

private:
    bool showCurrentPath = false;
    std::size_t currentPathIndex = 0;
    QVector<QPointF> defaultPath;
    QPointF m_firstSource;
    QVector<QVector<QPointF>> paths;
    QPointF m_destination;

private:
    const qreal m_drawing_radius = 24;
};

#endif // UAV_H

#ifndef VIEWER_H
#define VIEWER_H

#include <QGraphicsView>

namespace Display
{
    class Viewer;
}


class Display::Viewer : public QGraphicsView
{
    Q_OBJECT
public:
    Viewer(QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // VIEWER_H

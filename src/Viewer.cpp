#include "Viewer.h"
#include <QWheelEvent>

Display::Viewer::Viewer(QWidget *parent)
    : QGraphicsView (parent)
{

}

void Display::Viewer::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        // zoom
        qreal factor = 0.0;

        if (event->angleDelta().y() > 0)
        {
            // zoom in
            factor = 1.1;
        } else
        {
            // zoom out
            factor = 0.9;
        }

        scale(factor, factor);
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }

}

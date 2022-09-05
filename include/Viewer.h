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
};

#endif // VIEWER_H

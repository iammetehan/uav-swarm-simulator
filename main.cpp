#include <UAVSwarmSimulator.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UAVSwarmSimulator w;
    w.show();
    return a.exec();
}

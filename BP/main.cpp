#include <QApplication>
#include <QGraphicsScene>
#include <QApplication>
#include "World/Gridworld/gridworld.h"
#include "View/Gridworld/gridworldview.h"

World* world;
View* view;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    world = new Gridworld();
    view = world->getView();
    view->show();


    return a.exec();
}

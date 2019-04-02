#ifndef GRIDWORLDVIEW_AGENT_H
#define GRIDWORLDVIEW_AGENT_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QObject>

enum Color{
    BLUE, RED
};

class GridworldView_Agent: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:
    GridworldView_Agent(Color color);
};


#endif //GRIDWORLDVIEW_H

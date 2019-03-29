#ifndef GRIDWORLDVIEW_AGENT_H
#define GRIDWORLDVIEW_AGENT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class GridworldView_Agent: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    GridworldView_Agent();
};


#endif //GRIDWORLDVIEW_H

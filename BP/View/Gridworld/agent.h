#ifndef AGENT_H
#define AGENT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Agent: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Agent();
};


#endif //MYRECT

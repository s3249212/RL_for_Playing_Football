#define USEQT 0
#if USEQT == 1
#ifndef GRIDWORLDVIEW_BALL_H
#define GRIDWORLDVIEW_BALL_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QObject>

class GridworldView_Ball: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT

private:

public:
    GridworldView_Ball();
};


#endif //GRIDWORLDVIEW_H
#endif

#if USEQT == 1
#include <QBrush>
#include <QPen>

#include "gridworldview_ball.h"

GridworldView_Ball::GridworldView_Ball()
{
    setBrush(QBrush(QColor(255, 255, 255)));
    setPen(QPen(QColor(255,255,255)));
}
#endif
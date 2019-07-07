#if USEQT == 1
#include <QBrush>
#include <QPen>

#include "gridworldview_agent.h"

GridworldView_Agent::GridworldView_Agent(Color color)
{
    QColor c;
    switch(color){
    case BLUE:
        c.setRgb(0, 0, 255);
        break;
    case RED:
        c.setRgb(255, 0, 0);
        break;
    }

    setPen(QPen(c));
    setBrush(QBrush(c));
}
#endif
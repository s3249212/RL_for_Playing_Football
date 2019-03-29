#include <QBrush>

#include "agent.h"

GridworldView_Agent::GridworldView_Agent(Color color)
{
    QColor c;
    switch(color){
    case BLUE:
        c.setRgb(0, 0, 1);
        break;
    case RED:
        c.setRgb(1, 0, 0);
        break;
    }

    setBrush(QBrush(c));
}

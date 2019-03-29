#include <QtCore>

#include "agent.h"

GridworldView_Agent::GridworldView_Agent(Color color):
{
    QtGlobalColor c;
    switch(color){
    case BLUE:
        c = QtCore.Qt.blue;
        break;
    case RED:
        c = QtCore.Qt.red;
        break;
    }

    setBrush(QBrush(c, style = QtCore.Qt.SolidPattern);
}

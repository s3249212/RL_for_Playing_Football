#ifndef GRIDWORLD_H
#define GRIDWORLD_H

/*#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "score.h"
#include "health.h"*/
#include <array>
#include <vector>

#include "../world.h"
#include "../../View/view.h"

using namespace std;

class Gridworld : public World
{
private:
    View* view;

public:
    Gridworld();

    View* getView();
    int getHeight();
    int getWidth();

    vector<array<int, 2>> getBlueTeam();
    vector<array<int, 2>> getRedTeam();

    array<int, 2> getBall();
    int getGoalLength();
    View *v = new View();


};

#endif // GRIDWORLD_H

#ifndef GRIDWORLDVIEW_H
#define GRIDWORLDVIEW_H

#include "../../World/GridWorld/gridworld.h"
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <vector>

/*#include "player.h"
#include "score.h"
#include "health.h"*/
#include "agent.h"
#include "ball.h"
#include "goal.h"
#include "../view.h"


class GridworldView : public View
{
private:
    QGraphicsScene* scene;

    Gridworld world;

    vector<Agent*> agents;
    Ball* ball;
    Goal* goal0;
    Goal* goal1;

public:
    GridworldView(Gridworld& gridworld);


    /*Player* player;
    Score* score;
    Health* health;*/
};

#endif // GRIDWORLDVIEW_H

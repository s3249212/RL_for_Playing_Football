#ifndef GRIDWORLDVIEW_H
#define GRIDWORLDVIEW_H


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
#include "../../World/GridWorld/gridworld.h"

using namespace std;

class GridworldView : public View
{
private:
    QGraphicsScene* scene;

    Gridworld* world;

    vector<GridworldView_Agent*> blueteam;
    vector<GridworldView_Agent*> redteam;
    GridworldView_Ball* ball;

    double blockSize;

    int borderSize = 10;

    void setupViewCoordinates();
    array<int, 2> toViewCoord(int x, int y);

    void draw();

public:
    GridworldView(Gridworld& gridworld);
};

#endif // GRIDWORLDVIEW_H

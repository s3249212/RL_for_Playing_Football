#ifndef GRIDWORLDVIEW_H
#define GRIDWORLDVIEW_H


#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <vector>

#include "gridworldview_agent.h"
#include "gridworldview_ball.h"
#include "gridworldview_score.h"
#include "../view.h"
#include "../../World/Gridworld/gridworld.h"

using namespace std;

class GridworldView_Score;

class GridworldView : public View
{
Q_OBJECT
private:
    QGraphicsScene* scene;

    Gridworld* gridworld;

    vector<GridworldView_Agent*> blueteam;
    vector<GridworldView_Agent*> redteam;
    GridworldView_Ball* ball;

    double blockSize;

    int borderSize = 10;

    void setupViewCoordinates();
    array<int, 2> toViewCoord(int x, int y);


    QTimer* timer;

    GridworldView_Score* score;

public:
    GridworldView(Gridworld* gridworld);

    void initialize();
    //void draw();

    Gridworld* getWorld();

public slots:
    void draw();
};

#endif // GRIDWORLDVIEW_H

#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <array>
#include <vector>

#include "../world.h"
#include "../../View/view.h"
#include "gridworld_agent.h"
#include "gridworld_ball.h"

using namespace std;

class Gridworld_Agent;
class Gridworld_Ball;

class Gridworld : public World
{
private:
    enum Event{
        GOAL_BLUE = 0, GOAL_RED
    };

    int height = 30;
    int width = 50;


    vector<Gridworld_Agent*> redTeam;
    vector<Gridworld_Agent*> blueTeam;

    Gridworld_Ball* ball;

    vector<Event> eventLog;

    //vector<Player*> players;*/
public:
    Gridworld();

    void run();

    int getHeight();
    int getWidth();

    vector<array<int, 2>> getBlueTeam();
    vector<array<int, 2>> getRedTeam();

    array<int, 2> getBall();
    int getGoalLength();
};

#endif // GRIDWORLD_H

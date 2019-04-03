#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <array>
#include <vector>

#include "../world.h"
#include "../../View/view.h"
#include "gridworld_agent.h"
#include "gridworld_ball.h"
#include "gridworld_ih.h"
#include "gridworld_event.h"

using namespace std;

class Gridworld_Agent;
class Gridworld_Ball;
class Gridworld_IH;
class Gridworld_Event;

class Gridworld : public World
{
private:
    enum Event{
        GOAL_BLUE = 0, GOAL_RED
    };

    int height = 30;
    int width = 50;


    vector<Gridworld_Agent*> agents;

    Gridworld_Ball* ball;

    vector<Gridworld_Event*> eventLog;

    vector<Gridworld_IH*> ihs;

public:
    Gridworld();

    void run();

    int getHeight();
    int getWidth();

    vector<array<int, 2>> getBlueTeam();
    vector<array<int, 2>> getRedTeam();

    array<int, 2> getBall();
    int getGoalLength();

    void addIH(Gridworld_IH *ih);
    void addAgent(Gridworld_Agent* agent);

    vector<Gridworld_Event*> getEventLog();
};

#endif // GRIDWORLD_H

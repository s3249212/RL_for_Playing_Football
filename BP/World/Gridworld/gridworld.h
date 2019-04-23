#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <array>
#include <vector>
#include <QTimer>

#include "../world.h"
#include "../../View/view.h"
#include "gridworld_agent.h"
#include "gridworld_ball.h"
#include "Interaction_Handler/Gridworld/gridworld_ih.h"
#include "gridworld_score.h"
#include "gridworld_event.h"

using namespace std;

class Gridworld_Agent;
class Gridworld_Ball;
class Gridworld_IH;

class Gridworld : public World
{
private:
    enum Event{
        GOAL_BLUE = 0, GOAL_RED
    };

    int height = 20;
    int width = 30;
    int goallength = 10;


    vector<Gridworld_Agent*> agents;

    Gridworld_Ball* ball;

    vector<Gridworld_Event*> eventLog;

    vector<Gridworld_IH*> ihs;

    Gridworld_Score* score;

    Gridworld_IH* ih;

public:
    Gridworld();
    ~Gridworld();

    int getHeight();
    int getWidth();

    vector<array<int, 2>> getBlueTeam();
    vector<array<int, 2>> getRedTeam();

    array<int, 2> getBallCoord();
    Gridworld_Ball* getBall();

    int getGoalLength();

    void addIH(Gridworld_IH *ih);
    void addAgent(Gridworld_Agent* agent);

    vector<Gridworld_Event*> getEventLog();

    bool isWithinBounds(array<int, 2> coord);

    bool isInGoal(array<int, 2> coord);
    void updateAfterGoal(array<int, 2> coord);

    array<int, 2> getScore();

    void addEvent(Gridworld_Event::Event_type event_type, int team);

    void reset();

    void removeFromEventLog(Gridworld_Event *event);


public slots:
    void run();

};

#endif // GRIDWORLD_H

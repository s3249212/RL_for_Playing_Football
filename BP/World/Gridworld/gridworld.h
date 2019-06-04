#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <array>
#include <vector>

#include "../world.h"
#include "gridworld_agent.h"
#include "gridworld_ball.h"
#include "Interaction_Handler/Gridworld/gridworld_ih.h"
#include "gridworld_score.h"
#include "gridworld_event.h"

#include "Player/tabularq.h"
#include "Player/randomplayer.h"
#include "Player/mlpq.h"

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

    int height = 5;
    int width = 9;
    int goallength = 2;


    vector<Gridworld_Agent*> agents;

    Gridworld_Ball* ball;

    vector<Gridworld_Event*> eventLog;

    vector<Gridworld_IH*> ihs;

    Gridworld_Score* score;

    Gridworld_IH* ih;

    void runMatch(bool training);

    void saveStatistics();

    void resetEventLog();

public:
    Gridworld(string savefilename);
    ~Gridworld();

    void initialize();

    void addPlayer(TabularQ* player, int team);
    void addPlayer(RandomPlayer* player, int team);
    void addPlayer(MLPQ* player, int team);
    vector<Gridworld_IH*> getihs();
    int getHeight();
    int getWidth();

    vector<array<int, 2>> getTeam(int x);
    vector<array<int, 2>> getBlueTeam();
    vector<array<int, 2>> getRedTeam();

    array<int, 2> getBallCoord();
    Gridworld_Ball* getBall();

    int getGoalLength();

    void addIH(Gridworld_IH *ih);
    void addAgent(Gridworld_Agent* agent);

    vector<Gridworld_Event*> getEventLog();

    int hitsWall(array<int, 2> coord);
    bool hitsPlayer(array<int, 2> coord);
    bool hitsBall(array<int, 2> coord);
    bool isFree(array<int, 2> coord);
    bool isInGoal(array<int, 2> coord);
    void updateAfterGoal(array<int, 2> coord);

    array<int, 2> getScore();

    void addEvent(Gridworld_Event::Event_type event_type, int team);

    void runTraining();
    void runStep();

    void resetLocations();
    void resetAfterMatch();

    void removeFromEventLog(Gridworld_Event *event);

};

#endif // GRIDWORLD_H

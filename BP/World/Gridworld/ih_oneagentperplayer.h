#ifndef IH_ONEAGENTPERPLAYER_H
#define IH_ONEAGENTPERPLAYER_H

#include "gridworld_ih.h"
#include "gridworld.h"
#include "gridworld_agent.h"
#include "../../Player/player.h"

class IH_OneAgentPerPlayer: public Gridworld_IH
{
private:
    Gridworld_Agent* agent;
    Gridworld* world;
    Player* player;
    int team;

    int getReward();
    int numberOfAgents = 1;

public:
    IH_OneAgentPerPlayer(Player* player, int team);

    void setWorld(Gridworld* world);

    void update();
    void updateWorld(vector<int> action);

    int getTeam();

    int getNumberOfAgents();
    void addAgent(Gridworld_Agent* agent);
};

#endif // IH_ONEAGENTPERPLAYER_H

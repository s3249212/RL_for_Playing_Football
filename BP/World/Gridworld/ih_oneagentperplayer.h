#ifndef IH_ONEAGENTPERPLAYER_H
#define IH_ONEAGENTPERPLAYER_H

#include "interactionhandler.h"
#include "gridworld.h"
#include "gridworld_agent.h"

class IH_OneAgentPerPlayer: protected InteractionHandler
{
private:
    Gridworld_Agent* agent;
    Gridworld* world;
    int team;

    int getReward();

public:
    IH_OneAgentPerPlayer(Gridworld* world, Player* player, Gridworld_Agent* agent);

    void movement();
    void updateWorld(vector<int> action);

    int getTeam();
};

#endif // IH_ONEAGENTPERPLAYER_H

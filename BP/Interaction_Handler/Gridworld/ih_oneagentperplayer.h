#ifndef IH_ONEAGENTPERPLAYER_H
#define IH_ONEAGENTPERPLAYER_H

#include "gridworld_ih.h"
#include "World/Gridworld/gridworld.h"
#include "World/Gridworld/gridworld_agent.h"
#include "../../Player/player.h"

class IH_OneAgentPerPlayer: public Gridworld_IH
{
private:
    enum Team{
        SAME_PLAYER = 0, SAME_TEAM, PLAYER_TO_OPPONENT, OPPOSITE_TEAM
    };

    Gridworld_Agent* agent;
    Gridworld* world;
    Player* player;
    int team;

    int getReward();
    int numberOfAgents = 1;


    int** rewards;

public:
    IH_OneAgentPerPlayer(Player* player, int team);

    void setWorld(Gridworld* world);

    void update();
    void updateWorld(int action);

    int getTeam();

    int getNumberOfAgents();
    void addAgent(Gridworld_Agent* agent);

    Player* getPlayer(){return player;}

};

#endif // IH_ONEAGENTPERPLAYER_H

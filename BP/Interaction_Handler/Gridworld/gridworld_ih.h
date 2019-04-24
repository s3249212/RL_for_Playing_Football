#ifndef GRIDWORLD_IH_H
#define GRIDWORLD_IH_H

#include "Player/player.h"
#include "World/Gridworld/gridworld_agent.h"

class Gridworld_Agent;

class Gridworld_IH
{
/* Have one interaction handler with functions for each type of input and output.
 * Parameters given to the constructor determine which function will be used.
 */
private:
    int team;

    InputType inputType;

    void generateInput();
    void generateReward();
    void generateOutput();

public:
    enum InputType{
        BINARY_BLOCKS = 0
    };
    enum RewardType{
        GOAL_TOUCH = 0
    };
    enum OutputType{
        DEFAULT = 0
    };

    Gridworld_IH(/*InputType inputType, RewardType rewardType, OuputType outputType*/);

    virtual int getNumberOfAgents(){return 0;}
    virtual void addAgent(Gridworld_Agent* agent){};
    virtual void update(){};

    virtual int getTeam();
    virtual void setWorld(Gridworld* world){};

    virtual Player* getPlayer(){return NULL;}
};

#endif // GRIDWORLD_IH_H

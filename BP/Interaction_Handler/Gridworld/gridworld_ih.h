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

    Gridworld_IH(InputType inputType, RewardType rewardType, OuputType outputType);

    void update();

    void addAgent(Gridworld_Agent* agent);

    int getNumberOfAgents();
    int getTeam();
    Player* getPlayer();

    void setWorld(Gridworld* world);

private:
    Player* player;
    int team;

    InputType inputType;
    RewardType rewardType;
    OutputType outputType;

    void generateInput();
    void generateReward();
    void handleOutput(vector<int> output);

    vector<int> inputTabularQ();
};

#endif // GRIDWORLD_IH_H

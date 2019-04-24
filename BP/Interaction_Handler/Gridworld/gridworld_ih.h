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
        TabularQ = 0
    };
    enum RewardType{
        GOAL_TOUCH = 0
    };
    enum OutputType{
        DEFAULT_OUTPUT = 0
    };

    Gridworld_IH(Player *player, int team, int nAgents, Gridworld_IH::InputType inputType, Gridworld_IH::RewardType rewardType, OutputType outputType);

    void update();

    int getNumberOfAgents();
    int getTeam();
    Player* getPlayer();

    void addAgent(Gridworld_Agent* agent);
    void setWorld(Gridworld* world);

private:
    enum Event_actor{
        SAME_PLAYER = 0, SAME_TEAM, PLAYER_TO_OPPONENT, OPPOSITE_TEAM
    };

    Player* player;
    int team;
    int requiredNumberOfAgents;
    vector<Gridworld_Agent*> agents;
    Gridworld* world;

    int** rewards;

    InputType inputType;
    RewardType rewardType;
    OutputType outputType;

    vector<int> generateInput();
    int generateReward();
    void handleOutput(int output);

    vector<int> inputTabularQ();

    int rewardGoalTouch();

    void initRewardGeneration();
};

#endif // GRIDWORLD_IH_H

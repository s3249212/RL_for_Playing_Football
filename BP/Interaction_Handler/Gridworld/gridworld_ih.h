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
    enum Mode{
        TRAINING = 0, TEST
    };

    enum InputType{
    };
    enum RewardType{
        GOAL_TOUCH = 0
    };
    enum OutputType{
        DEFAULT_OUTPUT = 0
    };

    Gridworld_IH();

    virtual void update(bool terminal = 0);
    virtual void resetAfterMatch();

    int getNumberOfAgents();
    int getTeam();
    Player* getPlayer();

    void addAgent(Gridworld_Agent* agent);
    void setMode(Mode mode);

protected:
    Player* player;
    Gridworld* world;
    int team;

private:
    int requiredNumberOfAgents;
    vector<Gridworld_Agent*> agents;

    InputType inputType;
    RewardType rewardType;
    OutputType outputType;

    enum Event_actor{
        SAME_PLAYER = 0, SAME_TEAM, PLAYER_TO_OPPONENT, OPPOSITE_TEAM
    };
    
    int** rewards;

    virtual vector<int> generateInput(); //where to get input?
    virtual int generateReward();
    void handleOutput(int output);

    int rewardGoalTouch();

    void initRewardGeneration();
};

#endif // GRIDWORLD_IH_H

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

    void update(bool terminal = 0);
    void resetAfterMatch();

    int getNumberOfAgents();
    int getTeam();
    Player* getPlayer();

    void addAgent(Gridworld_Agent* agent);
    void setMode(Mode mode);

    string getStatistics();
    void resetMatchStatistics();

protected:
    Player* player;
    Gridworld* world;
    int team;

    vector<Gridworld_Agent*> agents;

private:
    Mode mode;

    int requiredNumberOfAgents = 1;

    InputType inputType;
    RewardType rewardType;
    OutputType outputType;

    enum Event_actor{
        SAME_PLAYER = 0, SAME_TEAM, PLAYER_TO_OPPONENT, OPPOSITE_TEAM
    };
    
    int** rewards;

    virtual vector<double> generateInput(); //where to get input?
    double generateReward();
    void handleOutput(int output);

    int rewardGoalTouch();

    void initRewardGeneration();

    int totalreward = 0;
};

#endif // GRIDWORLD_IH_H

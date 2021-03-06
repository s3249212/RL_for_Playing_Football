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
    ~Gridworld_IH();

    virtual void initialize() = 0;

    void updateEndEpisode();
    void update();
    void resetAfterEpisode();

    int getNumberOfAgents();
    int getTeam();
    Player* getPlayer();

    void addAgent(Gridworld_Agent* agent);
    void setMode(Mode mode);

    virtual string getStatistics();
    virtual void resetMatchStatistics();

    vector<Gridworld_Agent *> getAgents();

    void save(string filename);
    void load(string filename);

    double generateRewardEndEpisode();

    void clearAgents();

protected:
    Player* player;
    Gridworld* world;
    int team;

    vector<Gridworld_Agent*> agents;

    int totalreward = 0;

private:
    Mode mode = TRAINING;

    int requiredNumberOfAgents = 1;

    InputType inputType;
    RewardType rewardType = GOAL_TOUCH;
    OutputType outputType;

    enum Event_actor{
        SAME_PLAYER = 0, SAME_TEAM, PLAYER_TO_OPPONENT, OPPOSITE_TEAM
    };

    vector<double> prevInput;
    int prevAction = -1;
    
    int** rewards;

    virtual vector<double> generateInput(); //where to get input?
    double generateReward();
    void handleOutput(int output);

    int rewardGoalTouch();

    void initRewardGeneration();
    int rewardGoalTouchEndEpisode();
};

#endif // GRIDWORLD_IH_H

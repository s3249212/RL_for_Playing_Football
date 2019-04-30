#ifndef GRIDWORLD_SCORE_H
#define GRIDWORLD_SCORE_H

#include <array>

using namespace std;

class Gridworld_Score
{
private:
    int team0 = 0;
    int team1 = 0;

public:
    Gridworld_Score();

    void increaseScore(int team);
    array<int, 2> getScore();
    void reset();
};

#endif // GRIDWORLD_SCORE_H

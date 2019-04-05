#include "gridworld_score.h"

Gridworld_Score::Gridworld_Score()
{

}

void Gridworld_Score::increaseScore(int team)
{
    switch(team){
    case 0:
        team0++;
        break;
    case 1:
        team1++;
        break;
    }
}

array<int, 2> Gridworld_Score::getScore()
{
    return {team0, team1};
}


#ifndef RANDOMIH_H
#define RANDOMIH_H

#include "Interaction_Handler/Gridworld/gridworld_ih.h"

#include "World/Gridworld/gridworld.h"

#include "Player/randomplayer.h"

class RandomIH : public Gridworld_IH
{
public:
    RandomIH(Gridworld* gridworld, RandomPlayer* player, int team);

    /*string getStatistics();
    void resetMatchStatistics();*/

};

#endif // RANDOMIH_H

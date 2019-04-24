#ifndef TABULARQ_H
#define TABULARQ_H

#include "Player/player.h"

class TabularQ : public Player
{
public:
    TabularQ();

    int act(vector<int> input, int reward);
};

#endif // TABULARQ_H

#ifndef TABULARQIH_H
#define TABULARQIH_H

#include <vector>
#include "gridworld_ih.h"

class TabularQIH: public Gridworld_IH
{
public:
    TabularQIH(Gridworld* world, TabularQ* player, int team);

    void update(bool terminal = 0);
    void resetAfterMatch();

    vector<double> generateInput();

private:
    int getStateNumber(vector<double> input);

    TabularQ* tabularQPlayer;
};

#endif // TABULARQIH_H

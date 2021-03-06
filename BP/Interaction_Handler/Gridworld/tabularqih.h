#ifndef TABULARQIH_H
#define TABULARQIH_H

#include <vector>
#include "gridworld_ih.h"

class TabularQIH: public Gridworld_IH
{
public:
    TabularQIH(Gridworld* world, TabularQ* player, int team);

    void initialize();

    void update(bool terminal = false);
    void resetAfterEpisode();

    vector<double> generateInput();

    string getStatistics();
    /*void resetMatchStatistics();*/

private:
    int getStateNumber(vector<double> input);

    TabularQ* tabularQPlayer;
};

#endif // TABULARQIH_H

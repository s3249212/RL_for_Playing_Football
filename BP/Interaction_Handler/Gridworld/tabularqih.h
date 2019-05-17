#ifndef TABULARQIH_H
#define TABULARQIH_H

#include <vector>

class TabularQIH: public Gridworld_IH
{
public:
    TabularQIH(Gridworld* world, TabularQ* player, int team);

    void update(bool terminal = 0);
    void resetAfterMatch();

    vector<int> generateInput();

private:
    TabularQ* tabularQPlayer;
};

#endif // TABULARQIH_H

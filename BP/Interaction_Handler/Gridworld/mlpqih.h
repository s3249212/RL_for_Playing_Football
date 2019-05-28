#ifndef MLPQIH_H
#define MLPQIH_H

#include "gridworld_ih.h"


class MLPQIH: public Gridworld_IH
{
public:
    MLPQIH(Gridworld* gridworld, MLPQ* player, int team);

    void initialize();

    void update(bool terminal = 0);
    void resetAfterMatch();

    vector<double> generateInput();

private:
    MLPQ* MLPQPlayer;
};

#endif // MLPQIH_H

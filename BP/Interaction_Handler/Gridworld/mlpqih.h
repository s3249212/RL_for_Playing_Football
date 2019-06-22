#ifndef MLPQIH_H
#define MLPQIH_H

#include "gridworld_ih.h"


class MLPQIH: public Gridworld_IH
{
public:
    MLPQIH(Gridworld* gridworld, MLPQ* player, int team);

    void initialize();

    void update(bool terminal = false);
    void resetAfterEpisode();

    vector<double> generateInput();

private:
    MLPQ* MLPQPlayer;

    int nInput;
    vector<double>* input;
};

#endif // MLPQIH_H

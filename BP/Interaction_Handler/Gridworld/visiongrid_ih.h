#ifndef VISIONGRID_IH_H
#define VISIONGRID_IH_H

#include "gridworld_ih.h"

class VisionGrid_IH : public Gridworld_IH
{
public:
    VisionGrid_IH(Gridworld *gridworld, MLPQ *player, int team, vector<int> gridSizes);

    void initialize();

    void update(bool terminal = 0);
    void resetAfterMatch();

    vector<double> generateInput();
private:
    MLPQ* MLPQPlayer;

    vector<int> gridSizes;

    vector<double>* input;
};

#endif // VISIONGRID_IH_H

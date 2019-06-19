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

    int nInput;
    vector<double>* input;

    int nLayerBounds;
    int* layerBounds;

    int getInputIdx(int xIdx, int yIdx, int offset, int nDepth);
    int getGridArea(int xIdx, int yIdx);
    bool isInVisionGrid(int x, int y, int *xIdx, int *yIdx);
};

#endif // VISIONGRID_IH_H

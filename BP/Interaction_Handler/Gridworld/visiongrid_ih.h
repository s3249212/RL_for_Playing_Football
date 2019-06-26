#ifndef VISIONGRID_IH_H
#define VISIONGRID_IH_H

#include "gridworld_ih.h"

class VisionGrid_IH : public Gridworld_IH
{
public:
    VisionGrid_IH(Gridworld *gridworld, MLPQ *player, int team, vector<int> gridSizes = {1, 1, 10});

    void initialize();

    void update(bool terminal = false);
    void resetAfterEpisode();

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
    bool isYInVisionGrid(int y, int *yIdx);
    bool isXInVisionGrid(int x, int *xIdx);
    bool isXorYInVisionGrid(int value, int centre, int *idx);
    void addHorizontalLineToGrid(int x0, int x1, int y, int offset, int nDepth);
    void addVerticalLineToGrid(int y0, int y1, int x, int offset, int nDepth);
    void addLineToGrid(int x0, int y0, int x1, int y1, int offset, int nDepth);
};

#endif // VISIONGRID_IH_H

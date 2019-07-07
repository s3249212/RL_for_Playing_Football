#if USEQT == 1
#ifndef GRIDWORLDVIEW_SCORE_H
#define GRIDWORLDVIEW_SCORE_H

#include "gridworldview.h"

#include <QGraphicsTextItem>

class GridworldView;

class GridworldView_Score: public QGraphicsTextItem
{
private:
    GridworldView* view;

public:
    GridworldView_Score(GridworldView* view);

    void update();
};

#endif // GRIDWORLDVIEW_SCORE_H
#endif
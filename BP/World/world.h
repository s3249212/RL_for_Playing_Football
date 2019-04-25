#ifndef WORLD_H
#define WORLD_H

#include "../View/view.h"

class World
{
public:
    enum Mode{
        TEST = 0, TRAINING
    };

    View* getView();

    void runTraining();
    //void setPaused(int boolean);

    /*save load delete restart start (= run)*/

protected:
    View* view;

    int nBlocks = 100000000;

    int nTrainingPerBlock = 50;
    int nTestPerBlock = 10;

    virtual void runMatch(Mode mode){};
};

#endif // WORLD_H

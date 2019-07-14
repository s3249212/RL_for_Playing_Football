#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>
#include <sstream>

class World
{
public:
    enum Mode{
        TEST = 0, TRAINING
    };
    virtual void runTraining() = 0;
    //void setPaused(int boolean);

    /*save load delete restart start (= run)*/

protected:
    std::ofstream savefile;

    int nBlocks = 300 / 3;

    int nTrainingPerBlock = 0;
    int nTestPerBlock = 100;

    //virtual void runMatch(Mode mode) = 0;

    //virtual void saveStatistics() = 0;
};

#endif // WORLD_H

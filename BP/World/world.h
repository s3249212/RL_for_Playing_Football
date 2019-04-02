#ifndef WORLD_H
#define WORLD_H

#include "../View/view.h"

class World
{
protected:
    View* view;

public:
    World();
    View* getView();

    void run();
    //void setPaused(int boolean);

    /*save load delete restart start (= run)*/
};

#endif // WORLD_H

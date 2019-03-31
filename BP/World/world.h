#ifndef WORLD_H
#define WORLD_H

#include "../View/view.h"

class World
{

public:
    World();
    View* viewWorld;
    virtual View* getView();
};

#endif // WORLD_H

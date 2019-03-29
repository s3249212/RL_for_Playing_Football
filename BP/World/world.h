#ifndef WORLD_H
#define WORLD_H

#include "../View/view.h"

class World
{
public:
    World();

    virtual View* getView();
};

#endif // WORLD_H

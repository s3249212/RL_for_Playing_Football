#ifndef INTERACTIONHANDLER_H
#define INTERACTIONHANDLER_H

#include "../../Player/player.h"


class InteractionHandler
{
protected:
    Player* player;

    int reward;

    void generateReward();

public:
    InteractionHandler();

    virtual void updateWorld(){};
};

#endif // INTERACTIONHANDLER_H

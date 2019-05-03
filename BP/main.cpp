#include <QApplication>
#include <QGraphicsScene>
#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <thread>
#include <stdlib.h>
#include <time.h>

#include "World/Gridworld/gridworld.h"
#include "View/Gridworld/gridworldview.h"
#include "Player/player.h"
#include "Player/randomplayer.h"
#include "Player/tabularq.h"
#include "Interaction_Handler/Gridworld/gridworld_ih.h"

void threadFunction(Gridworld* gridworld){
    gridworld->runTraining();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    GridworldView* view;

    QApplication* a = new QApplication(argc, argv);

    Gridworld_IH::InputType inputType = Gridworld_IH::TabularQ;
    Gridworld_IH::RewardType rewardType = Gridworld_IH::GOAL_TOUCH;
    Gridworld_IH::OutputType outputType = Gridworld_IH::DEFAULT_OUTPUT;

    Gridworld* gridworld = new Gridworld();

    TabularQ* player = new TabularQ(gridworld);
    Gridworld_IH* ih = new Gridworld_IH(player, 0, 1, inputType, rewardType, outputType);
    gridworld->addIH(ih);

    Player* player2 = new RandomPlayer();
    ih = new Gridworld_IH(player2, 1, 1, inputType, rewardType, outputType);
    gridworld->addIH(ih);

    view = new GridworldView();
    view->setWorld(gridworld);
    view->show();

    //gridworld->runTraining();

    std::thread t1(threadFunction, gridworld);

    a->exec();

    t1.join();

    return 0;
}

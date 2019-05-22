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
    Gridworld* gridworld = new Gridworld("/home/julian/savefile31");

    TabularQ* player = new TabularQ();
    gridworld->addPlayer(player, 0);

    RandomPlayer* player2 = new RandomPlayer();
    gridworld->addPlayer(player2, 1);

    view = new GridworldView();
    view->setWorld(gridworld);
    view->show();

    gridworld->runTraining();

    //std::thread t1(threadFunction, gridworld);

    a->exec();

    //t1.join();

    return 0;
}

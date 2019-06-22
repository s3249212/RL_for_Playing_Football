#define USEQT 1
#if USEQT == 1
#include <QApplication>
#include <QGraphicsScene>
#include <QApplication>
#include <QTimer>
#include <QDebug>
#endif

#include <thread>
#include <stdlib.h>
#include <time.h>

#include "World/Gridworld/gridworld.h"
#if USEQT == 1
#include "View/Gridworld/gridworldview.h"
#endif
#include "Player/player.h"
#include "Player/randomplayer.h"
#include "Player/tabularq.h"
#include "Player/mlpq.h"
#include "Interaction_Handler/Gridworld/gridworld_ih.h"

void threadFunction(Gridworld* gridworld){
    gridworld->runTraining();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

#if USEQT == 1
    GridworldView* view;

    QApplication* a = new QApplication(argc, argv);
#endif
    Gridworld* gridworld = new Gridworld("/home/julian/savefile19");

    MLPQ* player = new MLPQ("/home/julian/playersavefile12_0");
    gridworld->addPlayer(player, 0);
    /*player = new MLPQ();
    gridworld->addPlayer(player, 0);*/

    RandomPlayer* player2 = new RandomPlayer();
    gridworld->addPlayer(player2, 1);
    /*player2 = new RandomPlayer();
    gridworld->addPlayer(player2, 1);*/

    gridworld->initialize();

#if USEQT == 1
    view = new GridworldView();
    view->setWorld(gridworld);
    view->show();
#endif

    vector<int> v = {1, 2, 4};

    //gridworld->runTraining();

    //std::thread t1(threadFunction, gridworld);

    a->exec();

    //t1.join();
    delete player;
    delete player2;
    delete gridworld;

    return 0;
}

#include <QApplication>
#include <QGraphicsScene>
#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <thread>
#include "World/Gridworld/gridworld.h"
#include "View/Gridworld/gridworldview.h"
#include "Player/player.h"
#include "Player/randomplayer.h"
#include "Interaction_Handler/Gridworld/ih_oneagentperplayer.h"
#include "Interaction_Handler/Gridworld/gridworld_ih.h"

World* world;

QApplication* a;
Gridworld* gridworld;

void threadFunction(){
    gridworld->run();
}

int main(int argc, char *argv[])
{
    GridworldView* view;
    a = new QApplication(argc, argv);

    Gridworld_IH::InputType inputType;

    /*Gridworld* */gridworld = new Gridworld();
    Player* player = new RandomPlayer();
    Gridworld_IH* ih = new IH_OneAgentPerPlayer(player, 0);
    gridworld->addIH(ih);

    /*player = new RandomPlayer();
    ih = new IH_OneAgentPerPlayer(player, 0);
    gridworld->addIH(ih);

    player = new RandomPlayer();
    ih = new IH_OneAgentPerPlayer(player, 0);
    gridworld->addIH(ih);

    player = new RandomPlayer();
    ih = new IH_OneAgentPerPlayer(player, 1);
    gridworld->addIH(ih);

    player = new RandomPlayer();
    ih = new IH_OneAgentPerPlayer(player, 1);
    gridworld->addIH(ih);*/

    Player* player2 = new RandomPlayer();
    ih = new IH_OneAgentPerPlayer(player2, 1);
    gridworld->addIH(ih);

    //view = gridworld->getView();
    view = new GridworldView();
    view->setWorld(gridworld);
    //view->initialize();
    view->show();
    //view->draw();

    std::thread t1(threadFunction);
    //view->draw();
    a->exec();

    t1.join();
    /*gridworld->run();
    view->update();*/


    qDebug() << player->totalReward;
    qDebug() << player2->totalReward;

   return 0;
}

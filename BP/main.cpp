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
#include "Player/tabularq.h"
#include "Interaction_Handler/Gridworld/ih_oneagentperplayer.h"
#include "Interaction_Handler/Gridworld/gridworld_ih.h"

World* world;

QApplication* a;
Gridworld* gridworld;

void threadFunction(){
    gridworld->runTraining();
}

int main(int argc, char *argv[])
{
    /*std::ofstream inputstream("~/savefile.txt");
    inputstream << "Heyo!" << std::endl;
    inputstream.close();*/
    GridworldView* view;
    a = new QApplication(argc, argv);

    Gridworld_IH::InputType inputType = Gridworld_IH::TabularQ;
    Gridworld_IH::RewardType rewardType = Gridworld_IH::GOAL_TOUCH;
    Gridworld_IH::OutputType outputType = Gridworld_IH::DEFAULT_OUTPUT;

    /*Gridworld* */gridworld = new Gridworld();
    TabularQ* player = new TabularQ(gridworld);
    //qDebug() << "Generating IH...";
    Gridworld_IH* ih = new Gridworld_IH(player, 0, 1, inputType, rewardType, outputType);
    //qDebug() << "Adding IH to world...";
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
    ih = new Gridworld_IH(player2, 1, 1, inputType, rewardType, outputType);
    gridworld->addIH(ih);

    //view = gridworld->getView();
    view = new GridworldView();
    view->setWorld(gridworld);
    //view->initialize();
    view->show();
    //view->draw();

    //gridworld->runTraining();

    std::thread t1(threadFunction);
    //view->draw();
    a->exec();

    t1.join();
    player->printQTable();
    /*gridworld->run();
    view->update();*/


    qDebug() << player->totalReward;
    //qDebug() << player2->totalReward;

   return 0;
}

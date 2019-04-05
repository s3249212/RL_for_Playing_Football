#include <QApplication>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include "World/Gridworld/gridworld.h"
#include "View/Gridworld/gridworldview.h"
#include "Player/player.h"
#include "Player/randomplayer.h"
#include "World/Gridworld/ih_oneagentperplayer.h"

World* world;

int main(int argc, char *argv[])
{
    View* view;
    QApplication a(argc, argv);

    Gridworld* gridworld = new Gridworld();
    RandomPlayer* player = new RandomPlayer();
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

    RandomPlayer* player2 = new RandomPlayer();
    ih = new IH_OneAgentPerPlayer(player, 1);
    gridworld->addIH(ih);

    view = gridworld->getView();
    view->initialize();
    view->show();
    view->draw();

    gridworld->run();
    //view->update();
    qDebug() << player->totalReward;
    qDebug() << player2->totalReward;

   return a.exec();
}

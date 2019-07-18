#define USEQT 0
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
#include <string>
#include <iostream>

#include "World/Gridworld/gridworld.h"
#if USEQT == 1
#include "View/Gridworld/gridworldview.h"
#endif
#include "Player/player.h"
#include "Player/randomplayer.h"
#include "Player/tabularq.h"
#include "Player/mlpq.h"
#include "Player/qv.h"
#include "Interaction_Handler/Gridworld/gridworld_ih.h"

void threadFunction(Gridworld* gridworld){
    gridworld->runTraining();
}

int main(int argc, char *argv[])
{
	if(argc < 2){
		return -1;
	}
	cout << argv[1];
	
    srand(time(NULL));

#if USEQT == 1
    GridworldView* view;

    QApplication* a = new QApplication(argc, argv);
#endif
    Gridworld* gridworld = new Gridworld(argv[1]);

    MLPQ* player = new MLPQ();
    gridworld->setType(player, 0, 1, 7);

    RandomPlayer* player2 = new RandomPlayer();
    gridworld->setType(player2, 1, 7);

    gridworld->initialize();

#if USEQT == 1
    view = new GridworldView();
    view->setWorld(gridworld);
    view->show();
#endif

    gridworld->runTraining();

    //Run tests on different field sizes and team sizes
    for(Gridworld_IH* ih: gridworld->getLeftType(){
		ih->setMode(Gridworld_IH::TEST);
    }

    for(Gridworld_IH* ih: gridworld->getRightType()){
      ih->setMode(Gridworld_IH::TEST);
    }

    gridworld->setVariations(false, false, true);
    
    int nTestPerSetting = 100;
    vector<int> nPlayersToBeTested = {1, 2, 5, 7};
    vector<array<int, 2>> sizes;
    sizes.push_back({9, 9});
    sizes.push_back({15, 15});
    sizes.push_back({25, 25});
    

	for(array<int, 2> size: sizes){
		gridworld->setwidth(size[0]);
		gridworld->setHeight(size[1]);
		for(int nPlayers: nPlayersToBeTested){
			gridworld->setNPlayers(nplayers);
			for(int i = 0 ; i < nTestPerSetting; i++){
				gridworld->runMatch();
				gridworld->saveStatistics();
				gridworld->resetAfterMatch();
			}
		}
	}
	
    delete player;
    delete player2;
    delete gridworld;

    return 0;
}

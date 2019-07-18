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

    /*RandomPlayer* player = new RandomPlayer();
    gridworld->setType(player, 0, 7);*/

    RandomPlayer* player2 = new RandomPlayer();
    gridworld->setType(player2, 1, 7);

    gridworld->initialize();

#if USEQT == 1
    view = new GridworldView();
    view->setWorld(gridworld);
    view->show();
    a->exec();
#endif

    gridworld->runTraining();

    //Run tests on different field sizes and team sizes
    for(Gridworld_IH* ih: gridworld->getLeftType()){
		ih->setMode(Gridworld_IH::TEST);
    }

    for(Gridworld_IH* ih: gridworld->getRightType()){
      ih->setMode(Gridworld_IH::TEST);
    }

    gridworld->setVariations(false, false, true);
    
    int nTestPerSetting = 100;
    vector<int> nPlayersToBeTested = {1, 2, 5, 7};
    vector<array<int, 3>> sizes;
    sizes.push_back({9, 9, 3});
    sizes.push_back({15, 15, 5});
    sizes.push_back({25, 25, 5});
    

    int cnt = 0, nTests = sizes.size() * nPlayersToBeTested.size() * nTestPerSetting;
    cout << "Running tests..." << endl;
    for(array<int, 3> size: sizes){
        gridworld->setWidth(size[0]);
		gridworld->setHeight(size[1]);
        gridworld->setGoalLength(size[2]);
		for(int nPlayers: nPlayersToBeTested){
            gridworld->setNPlayers(nPlayers);
            gridworld->setSaveFile(to_string(size[0]) + "_" + to_string(size[1]) + "_" + to_string(nPlayers));
			for(int i = 0 ; i < nTestPerSetting; i++){
                cout << "Test " << cnt + 1 << " out of " << nTests << " total. Width: " << size[0] << ", height: " << size[1] << ", goal length: " << size[2] << ", number of players: " << nPlayers << ", match " << i + 1 << " out of " << nTestPerSetting << "." << endl;
                gridworld->runMatch(0);
				gridworld->saveStatistics();
				gridworld->resetAfterMatch();
                cnt++;
			}
		}
	}
	
    delete player;
    delete player2;
    delete gridworld;

    return 0;
}

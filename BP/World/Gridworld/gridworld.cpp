#include <string>
#include <iostream>
#include <time.h>

#include "gridworld.h"
#include "gridworld_agent.h"
#include "gridworld_score.h"
#include "gridworld_ball.h"

#include "Interaction_Handler/Gridworld/gridworld_ih.h"

using namespace std;

Gridworld::Gridworld(string savefilename):
savefilename(savefilename)
{
    ball = new Gridworld_Ball(this, {width / 2, height/2});
    score = new Gridworld_Score();

    initializationTime = static_cast<int>(time(NULL));
    cout << initializationTime << endl << endl;
    savefile.open(savefilename + "savefile_" + to_string(initializationTime));
    playersavefilename = savefilename + "playersavefile_" + to_string(initializationTime) + "_";
}

Gridworld::~Gridworld(){
    savefile.close();
    resetEventLog();
    delete ball;
    for(Gridworld_Agent* a: agents){
        delete a;
    }
    for(Gridworld_IH* ih: ihs){
        delete ih;
    }
    delete score;
}

void Gridworld::initialize()
{
    if(varyFieldSizes){
        changeFieldSize();
    }
    if(varyTeamSizes){
        changeTeamSizes();
    }
    for(Gridworld_IH* ih: ihs){
        //ih->initialize();
    }
}

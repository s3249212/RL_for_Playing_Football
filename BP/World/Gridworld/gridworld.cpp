#include <chrono>
#include <vector>
#include <iostream>

#include "gridworld.h"
#include "gridworld_agent.h"
#include "gridworld_score.h"

#include "Interaction_Handler/Gridworld/tabularqih.h"
#include "Interaction_Handler/Gridworld/randomih.h"
#include "Interaction_Handler/Gridworld/mlpqih.h"

using namespace std;
using namespace std::chrono;

void Gridworld::runTraining(){
    for(int i = 0; i < nBlocks; i++){
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        for(int j = 0; j < nTrainingPerBlock; j++){
            runMatch(TRAINING);
            resetAfterMatch();
        }

        for(int j = 0; j < nTestPerBlock; j++){
            cout << "Running match: " << j << endl;
            runMatch(TEST);
            saveStatistics();
            resetAfterMatch();
        }

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        auto expectedTime = duration * (nBlocks - i - 1);

        cout << "Block: " << i << " out of " << nBlocks << ". Duration of a match: " << duration << ". Expected time left: " << expectedTime / 3600000000 << " hours, " << expectedTime % 3600000000 / 60000000 << " minutes, " << expectedTime % 60000000 / 1000000 << " seconds, " << expectedTime % 1000000 << " microseconds." << endl;
    }
}

void Gridworld::runMatch(bool training = 0){
    Gridworld_IH::Mode mode;

    if(training){
        mode = Gridworld_IH::TRAINING;
    } else {
        mode = Gridworld_IH::TEST;
    }

    for(Gridworld_IH* ih: ihs){
        ih->setMode(mode);
    }

    for(int i = 0; i < 10000; i++){
        runStep();
    }

    for(Gridworld_IH* ih: ihs){
        //ih->update(true);
        ih->resetAfterMatch();
    }
}

void Gridworld::runStep(){
    for(Gridworld_IH* ih: ihs){
        this->ih = ih;
        ih->update();
        ball->automaticMove();
    }
}

void Gridworld::saveStatistics(){
    for(int i = 0; i < ihs.size(); i++){
        Gridworld_IH* ih = ihs.at(i);
        if(i > 0){
            savefile << "\t";
        }
        savefile << ih->getStatistics();
    }
    savefile << endl;
}

Gridworld::Gridworld(string savefilename){
    ball = new Gridworld_Ball(this, {width / 2, height/2});
    score = new Gridworld_Score();

    savefile.open(savefilename);
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
    for(Gridworld_IH* ih: ihs){
        ih->initialize();
    }
}

void Gridworld::addPlayer(TabularQ *player, int team)
{
    Gridworld_IH* ih = new TabularQIH(this, player, team);
    addIH(ih);
}

void Gridworld::addPlayer(MLPQ *player, int team)
{
    Gridworld_IH* ih = new MLPQIH(this, player, team);
    addIH(ih);
}

vector<Gridworld_IH *> Gridworld::getihs()
{
    return ihs;
}

void Gridworld::addPlayer(RandomPlayer *player, int team){
    Gridworld_IH* ih = new RandomIH(this, player, team);
    addIH(ih);
}

void Gridworld::addIH(Gridworld_IH *ih){
    ihs.push_back(ih);

    int nAgents = ih->getNumberOfAgents();
    for(int i = 0; i < nAgents; i++){
        int x = ih->getTeam() == 0? getBlueTeam().size() + 1: width - 2 - getRedTeam().size();

        Gridworld_Agent * agent = new Gridworld_Agent(this, ih->getTeam(), {x, 1});

        addAgent(agent);
        ih->addAgent(agent);
    }
}

void Gridworld::addAgent(Gridworld_Agent *agent){
    agents.push_back(agent);
}

int Gridworld::hitsWall(array<int, 2> coord){
    int n = 0; //number of wall

    int x = coord[0];
    int y = coord[1];

    if(y == 0){
        n += 1;
    }
    if(y == height - 1){
        n += 2;
    }
    if(x == 0){
        n += 6;
    }
    if(x == width - 1){
        n += 3;
    }

    return n;
}

bool Gridworld::hitsPlayer(array<int,2> coord){
    bool p = false;

    for(Gridworld_Agent* a: agents){
        if(coord == a->getCoord()){
            p = true;
        }
    }

    return p;
}

bool Gridworld::hitsBall(array<int, 2> coord){
    return coord == ball->getCoord();
}

bool Gridworld::isFree(array<int, 2> coord){
    return !hitsWall(coord) && !hitsPlayer(coord) && !hitsBall(coord);
}

bool Gridworld::isInGoal(array<int, 2> coord)
{
    int min = height / 2 - goallength;
    int max = height / 2 + goallength;

    return (coord[0] == 0 || coord[0] == width - 1) &&
            coord[1] >= min && coord[1] <= max;
}

void Gridworld::updateAfterGoal(array<int, 2> coord)
{
    int team;
    if(coord[0] == 0){
        team = 1;
    } else {
        team = 0;
    }

    score->increaseScore(team);

    addEvent(Gridworld_Event::GOAL, team);

    resetLocations();
}

void Gridworld::addEvent(Gridworld_Event::Event_type event_type, int team)
{
    Gridworld_Event* event = new Gridworld_Event();
    event->event_type = event_type;
    event->team = team;
    event->player = ih->getPlayer();
    eventLog.push_back(event);
}

void Gridworld::resetAfterMatch(){
    resetLocations();
    score->reset();
    resetEventLog();
}

void Gridworld::resetEventLog(){
    for(Gridworld_Event* e: eventLog){
        delete e;
    }
    eventLog.clear();
}

void Gridworld::resetLocations(){
    int nred = 0, nblue = 0;
    for(Gridworld_Agent* agent: agents){
        int x;
        if(agent->getTeam() == 0){
            x = nblue + 1;
            nblue++;
        } else {
            x = width - 2 - nred;
            nred++;
        }
        agent->setCoord({x, 1});
    }

    ball->setCoord({width / 2, height / 2});
}

void Gridworld::removeFromEventLog(Gridworld_Event *event)
{
     std::vector<Gridworld_Event *>::iterator i = std::find(eventLog.begin(), eventLog.end(), event);
     eventLog.erase(i);
     delete event;
}

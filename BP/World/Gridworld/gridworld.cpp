#include <chrono>
#include <vector>
#include <QDebug>
#include "gridworld.h"
#include "gridworld_agent.h"
#include "../../View/Gridworld/gridworldview.h"

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
            runMatch(TEST);
            saveStatistics();
            resetAfterMatch();
                        //qDebug() << "Duration of a match: " << duration;
        }
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        auto expectedTime = duration * (nBlocks - i - 1);
        qDebug() << "Block:" << i << "out of" << nBlocks << ". Duration of a match: " << duration << ". Expected time left:" << expectedTime / 3600000000 << "hours," << expectedTime % 3600000000 / 60000000 << "minutes," << expectedTime % 60000000 / 1000000 << "seconds," << expectedTime % 1000000 << "microseconds.";
    }
}

void Gridworld::runMatch(World::Mode mode){
    for(Gridworld_IH* ih: ihs){
        ih->getPlayer()->setMode(mode);
    }
    for(int i = 0; i < 10000; i++){
        //cout << "Run step" << endl;
        runStep();
    }
}

void Gridworld::runStep(){
    for(Gridworld_IH* ih: ihs){
        this->ih = ih;
        ih->update();
    }
}

void Gridworld::saveStatistics(){
    for(int i = 0; i < ihs.size(); i++){
        Gridworld_IH* ih = ihs.at(i);
        if(i > 0){
            savefile << "\t";
        }
        savefile << score->getScore()[ih->getTeam()] << "\t" << ih->getPlayer()->totalReward;
        ih->getPlayer()->totalReward = 0;
    }
    savefile << endl;
}

Gridworld::Gridworld(){
    //view = new GridworldView(this);
    ball = new Gridworld_Ball(this, {width / 2, height/2});
    score = new Gridworld_Score();

    //qDebug() << "Creating savefile\n";
    savefile.open("/home/julian/savefile");
}

Gridworld::~Gridworld(){
    savefile.close();
}

/*Gridworld::run(){
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < players.size(); j++){
            array<int, 3> actions = players.at(j)->act({1, 2, 3}, {1});
            updateState(j, actions);
        }
    }
}

Gridworld::updateState(int currentPlayer, array<int, 3> actions){
    Player* player = players.at(currentPlayer);
    Agent* agent = player->getAgent();

}*/

/*void Gridworld::run(){
    for(int i = 0; i < 10000000; i++){
        getEventLog();
        for(Gridworld_IH* ih: ihs){
            this->ih = ih;
            ih->update();
        }
        //view->draw();
    }
}*/

array<int, 2> Gridworld::getBallCoord(){
    return ball->getCoord();
}

Gridworld_Ball* Gridworld::getBall(){
    return ball;
}

vector<array<int,2>> Gridworld::getTeam(int x){
    vector <array <int, 2>> team;
    for(Gridworld_Agent* a: agents){
        if(a->getTeam() == x){
            team.push_back(a->getCoord());
        }
    }
    return team;
}

vector<array<int,2>> Gridworld::getBlueTeam(){
    return getTeam(0);

    /*vector <array <int, 2>>* blue = new vector<array <int, 2>>;
    for(Gridworld_Agent* b: agents){
        if(b->getTeam() == 0){
            blue->push_back(b->getCoord());
        }
    }
    return *blue;*/
}

vector<array<int,2>> Gridworld::getRedTeam(){
    return getTeam(1);
    /*vector <array <int, 2>> red;
    for(auto r: agents){
        if(r->getTeam() == 1){
            red.push_back(r->getCoord());
        }
    }
    return red;*/
}

int Gridworld::getGoalLength(){
    return goallength;
}

int Gridworld::getWidth(){
    return width;
}

int Gridworld::getHeight(){
    return height;
}

void Gridworld::addIH(Gridworld_IH *ih){
    //qDebug() << "Adding IH";
    ihs.push_back(ih);
    int nAgents = ih->getNumberOfAgents();
    for(int i=0; i<nAgents; i++){
        int x = ih->getTeam() == 0? getBlueTeam().size() + 1: width - 2 - getRedTeam().size();
        Gridworld_Agent * agent = new Gridworld_Agent(this, ih->getTeam(), {x, 1});
        addAgent(agent);
        ih->addAgent(agent);
        ih->setWorld(this);
    }
}

void Gridworld::addAgent(Gridworld_Agent *agent){
    agents.push_back(agent);
}

vector<Gridworld_Event*> Gridworld::getEventLog(){
    return eventLog;
}

bool Gridworld::isWithinBounds(array<int, 2> coord){
    bool b = true;

    b = b && coord[0] > 0;
    b = b && coord[0] < width - 1;
    b = b && coord[1] > 0;
    b = b && coord[1] < height -1;

    b = b && coord != ball->getCoord();

    for(Gridworld_Agent* a: agents){
        b = b && coord != a->getCoord();
    }

    return b;
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

array<int, 2> Gridworld::getScore()
{
    return score->getScore();
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
}

void Gridworld::resetLocations(){
    int nred = 0, nblue = 0;
    for(Gridworld_Agent* agent: agents){
        int x;
        if(ih->getTeam() == 0){
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
}

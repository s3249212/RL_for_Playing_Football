#include <chrono>

#include "gridworld.h"

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
            cout << "Running match: " << j << " " << duration_cast<microseconds>( high_resolution_clock::now() - t1 ).count() << endl;
            runMatch(TEST);
            saveStatistics();
            resetAfterMatch();
        }

        int k = 0;
        for(Gridworld_IH* ih: ihs){
            ih->save(playersavefilename + to_string(k));
            k++;
        }
        //writeStatistics();

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
        ih->updateEndEpisode();
        ih->resetAfterEpisode();
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

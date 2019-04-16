#include "randomplayer.h"
#include <QDebug>
#include <stdlib.h>

RandomPlayer::RandomPlayer()
{

}

int RandomPlayer::act(vector<int> input, int reward){
    if(reward != 0){
        //qDebug() << "In act" << reward;
    }
    totalReward += reward;
    return rand() % 8;
}

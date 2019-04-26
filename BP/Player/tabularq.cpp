#include "tabularq.h"

#include <stdlib.h>

TabularQ::TabularQ()
{

}

int TabularQ::act(vector<int> input, int reward){
    totalReward += reward;
    return rand() % 8;
}


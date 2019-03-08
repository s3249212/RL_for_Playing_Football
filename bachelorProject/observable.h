//
// Created by 김유진 on 2019-03-01.
//

#ifndef BACHELORPROJECT_OBSERVABLE_H
#define BACHELORPROJECT_OBSERVABLE_H

using namespace std;

#include <vector>
#include "observer.h"

class Observable {
    vector<Observer> observers;

    protected:
        void notifyObservers();

    public:
        void addObserver(Observer observer);
};
#endif //BACHELORPROJECT_OBSERVABLE_H

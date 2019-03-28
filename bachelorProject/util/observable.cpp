//
// Created by 김유진 on 2019-03-01.
//

#include "observable.h"

void Observable::notifyObservers() {
    for(auto observer: observers){
        observer.update();
    }
}

void Observable::addObserver(Observer observer) {
    observers.push_back(observer);
}
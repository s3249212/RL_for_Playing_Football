#include "viewGridWorld.h"
#include "iostream"

ViewGridWorld::ViewGridWorld(GridWorld* gridw) :
    gridWorld(gridw) {
    }

void ViewGridWorld::render() {
    std::cout << endl;
}
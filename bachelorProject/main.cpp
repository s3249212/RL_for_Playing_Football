#include <iostream>
#include <vector>
#include "view.h"
#include "world.h"
#include "controller.h"

enum RL_Algorithm_Type{
    1 = q_learning;
};

int main() {

    std::vector<double> v;

    int n;
    Player p;
    World w;
    w.addPlayer(p);

    //std::cout << "Type your algorithm : " << std::endl;
    //std::cout << "0: 1: 2: " << std::endl;
    //std::cin >> n;
    return 0;
}
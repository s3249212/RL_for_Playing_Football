#ifndef DQN_H
#define DQN_H

#include <string>

//#include "Util/cnn.h"

using namespace std;

class dqn
{
public:
    dqn();
    dqn(string filename = "");

    ~dqn();

private:
    string sourcefile;

    //void load(string filename);

    //CNN* cnn;
};

#endif // DQN_H

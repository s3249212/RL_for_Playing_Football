#include "gridworldview.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <array>
#include <vector>

using namespace std;

GridworldView::GridworldView(Gridworld& gridworld)
{
    //create a view for the gridworld
    //it will take the gridworld object as an argument
    //it will setup the view by reading from that object
    //it will read the number of agents and create graphics items for them
    //it will create an item for the ball and goals.
    //it will read the current location of all agents and ball from the object.
    //it will scale the locations to match the view
    //it will place the items in the correct location.

    //it will have either an update function that will be called from the gridworld
    //or it will update a set number of times per second using a clock.

    //it will use a render boolean to determine whether it should output to the screen
    //this is aimed to make it quicker to run

    //it should have a destructor that cleans it properly.

    //create a scene
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);

    setBackgroundBrush(QBrush(QImage(":/images/field.png").scaled(800,600)));
    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    //createn an item to put into the scene

    //add the item to the scene
    scene->addItem(player);

    vector<array<double, 2>> gw_agents = gridworld.getAgents();
    for(array<double, 2> gw_a : gw_agents){
        Agent* agent = new Agent();
        agent->setPos(gw_a[0], gw_a[1]);
        scene->addItem(agent);
        agents.pushBack(agent);
    }

    gridworld.getBall();
}



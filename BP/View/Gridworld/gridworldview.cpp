#include "gridworldview.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QtCore>
#include <QBrush>
#include <QImage>
#include <array>
#include <vector>
#include "agent.h"

using namespace std;

void GridworldView::setupViewCoordinates(){
    int w = width();
    int h = height();

    w -= borderSize;
    h -= borderSize;

    double blockSizeWidth = w / (world->getWidth() + 2);
    double blockSizeHeight = h / (world->getHeight());

    blockSize = blockSizeWidth < blockSizeHeight? blockSizeWidth: blockSizeHeight;
}

array<int, 2> GridworldView::toViewCoord(int x, int y){
    double centreX = (double) width() / 2;
    double centreY = (double) height() / 2;

    double originX = centreX - (double)world->getWidth() / 2 * blockSize;
    double originY = centreY - (double)world->getHeight() / 2 * blockSize;

    double viewX = originX + blockSize * x;
    double viewY = originY + blockSize * y;

    array<int, 2> coord;
    coord[0] = (int) viewX;
    coord[1] = (int) viewY;

    return coord;
}

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

    setupViewCoordinates();

    vector<array<int, 2>> gw_agents = gridworld.getBlueTeam();
    for(int i = 0; i < gw_agents.size(); i++){
        GridworldView_Agent* agent = new GridworldView_Agent(BLUE);
        scene->addItem(agent);
        blueteam.push_back(agent);
    }

    gw_agents = gridworld.getRedTeam();
    for(int i = 0; i < gw_agents.size(); i++){
        GridworldView_Agent* agent = new GridworldView_Agent(RED);
        scene->addItem(agent);
        redteam.push_back(agent);
    }

    ball = new GridworldView_Ball();
    scene->addItem(ball);

    int goalsize = gridworld.getGoalLength();

    int goalY = gridworld.getHeight() / 2 - goalsize + gridworld.getHeight() % 2;
    array<int, 2> coord = toViewCoord(-1, goalY);
    QGraphicsRectItem* goal = new QGraphicsRectItem();
    goal->setRect(coord[0], coord[1], 2 * blockSize, (2 * goalsize - gridworld.getHeight() % 2) * blockSize);
    scene->addItem(goal);

    coord = toViewCoord(gridworld.getWidth() - 1, goalY);
    goal = new QGraphicsRectItem();
    goal->setRect(coord[0], coord[1], 2 * blockSize, (2 * goalsize - gridworld.getHeight() % 2) * blockSize);
    scene->addItem(goal);

    QGraphicsRectItem* line = new QGraphicsRectItem();
    line->setRect(0, 0, gridworld.getWidth() * blockSize, blockSize);
    line->setBrush(QBrush(QtCore.Qt.white, style = QtCore.Qt.SolidPattern);
    scene->addItem(line);

    line = new QGraphicsRectItem();
    line->setRect(0, 1, blockSize, (goalY - 1) * blockSize);
    line->setBrush(QBrush(QtCore.Qt.white, style = QtCore.Qt.SolidPattern);
    scene->addItem(line);

    line = new QGraphicsRectItem();
    line->setRect(gridworld.getWidth() - 1, 1, blockSize, (goalY - 1) * blockSize);
    line->setBrush(QBrush(QtCore.Qt.white, style = QtCore.Qt.SolidPattern);
    scene->addItem(line);

    int goalY2 = goalY + 2 * goalsize - gridworld.getHeight() % 2;
    coord = toViewCoord(0, goalY2);
    line = new QGraphicsRectItem();
    line->setRect(0, coord[1], blockSize, (goalY - 1) * blockSize);
    line->setBrush(QBrush(QtCore.Qt.white, style = QtCore.Qt.SolidPattern);
    scene->addItem(line);

    line = new QGraphicsRectItem();
    line->setRect(gridworld.getWidth() - 1, coord[1], blockSize, (goalY - 1) * blockSize);
    line->setBrush(QBrush(QtCore.Qt.white, style = QtCore.Qt.SolidPattern);
    scene->addItem(line);

    line = new QGraphicsRectItem();
    line->setRect(gridworld.getHeight() - 1, 0, gridworld.getWidth() * blockSize, blockSize);
    line->setBrush(QBrush(QtCore.Qt.white, style = QtCore.Qt.SolidPattern);
    scene->addItem(line);
}

void GridworldView::draw(){
    vector<array<int, 2>> gw_agents = gridworld.getBlueTeam();
    for(int i = 0; i < blueteam.size(); i++){
        array<int, 2> gw_a = gw_agents.at(i);
        array<int, 2> viewCoord = toViewCoord(gw_a[0], gw_a[1]);
        blueteam.at(i).setPos(viewCoord[0], viewCoord[1]);
    }

    gw_agents = gridworld.getRedTeam();
    for(int i = 0; i < gw_agents.size(); i++){
        array<int, 2> gw_a = gw_agents.at(i);
        array<int, 2> viewCoord = toViewCoord(gw_a[0], gw_a[1]);
        redteam.at(i).setPos(viewCoord[0], viewCoord[1]);
    }

    array<int, 2> ballcoords = gridworld.getBall();
}



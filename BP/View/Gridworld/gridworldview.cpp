#include "gridworldview.h"
#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QWidget>
#include <QtCore>
#include <QBrush>
#include <QImage>
#include <QTimer>
#include <array>
#include <vector>
#include "gridworldview_agent.h"
#include "gridworldview_score.h"

using namespace std;

class GridworldView_Score;

void GridworldView::setupViewCoordinates(){
    int w = width();
    int h = height();

    w -= 2 * borderSize;
    h -= 2 * borderSize;

    double blockSizeWidth = static_cast<double> (w) / (gridworld->getWidth() + 2);
    double blockSizeHeight = static_cast<double> (h) / (gridworld->getHeight());

    blockSize = blockSizeWidth < blockSizeHeight? blockSizeWidth: blockSizeHeight;
}

array<int, 2> GridworldView::toViewCoord(int x, int y){
    double centreX = static_cast<double> (width()) / 2;
    double centreY = static_cast<double> (height()) / 2;

    double originX = centreX - static_cast<double> (gridworld->getWidth()) / 2 * blockSize;
    double originY = centreY - static_cast<double> (gridworld->getHeight()) / 2 * blockSize;

    double viewX = originX + blockSize * x;
    double viewY = originY + blockSize * y;

    array<int, 2> coord;
    coord[0] = static_cast<int> (viewX);
    coord[1] = static_cast<int> (viewY);

    return coord;
}

GridworldView::GridworldView(QWidget* parent):
    View(parent)
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

    //initialize();
    //it should have a destructor that cleans it properly.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(draw()));
    //timer->start(1000.0 / 60.0);
}

void GridworldView::setWorld(Gridworld* world){
    gridworld = world;

    initialize();
    timer->start(1000.0 / 60.0);
}

/*void GridworldView::update(){
    //gridworld->run();
    //qDebug() << "Updating";
}*/

void GridworldView::initialize(){
    //create a scene
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);

    //setBackgroundBrush(QBrush(QImage(":/images/field.png").scaled(800,600)));
    QColor darkgreen(0.7 * 255, 1 * 255, 0.6 * 255);
    setBackgroundBrush(QBrush(darkgreen));
    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    setupViewCoordinates();

    vector<array<int, 2>> gw_agents = gridworld->getBlueTeam();
    for(unsigned i = 0; i < gw_agents.size(); i++){
        GridworldView_Agent* agent = new GridworldView_Agent(BLUE);
        scene->addItem(agent);
        blueteam.push_back(agent);
    }

    gw_agents = gridworld->getRedTeam();
    for(unsigned i = 0; i < gw_agents.size(); i++){
        GridworldView_Agent* agent = new GridworldView_Agent(RED);
        scene->addItem(agent);
        redteam.push_back(agent);
    }

    ball = new GridworldView_Ball();
    scene->addItem(ball);

    QColor black(0,0,0);
    QBrush blackBrush(black);
    //whiteBrush.setColor(Qt::white);
    QPen blackPen;
    blackPen.setColor(Qt::black);
    int goalsize = gridworld->getGoalLength();

    int goalY = gridworld->getHeight() / 2 - goalsize + gridworld->getHeight() % 2;
    array<int, 2> coord = toViewCoord(-1, goalY);
    QGraphicsRectItem* goal = new QGraphicsRectItem();
    goal->setRect(coord[0], coord[1], 2 * blockSize, (2 * goalsize - gridworld->getHeight() % 2) * blockSize - 1);
    goal->setBrush(blackBrush);
    goal->setPen(blackPen);
    scene->addItem(goal);

    coord = toViewCoord(gridworld->getWidth() - 1, goalY);
    goal = new QGraphicsRectItem();
    goal->setRect(coord[0], coord[1], 2 * blockSize, (2 * goalsize - gridworld->getHeight() % 2) * blockSize - 1);
    goal->setBrush(blackBrush);
    goal->setPen(blackPen);
    scene->addItem(goal);

    QColor white(255,255,255);
    QBrush whiteBrush(white);
    //whiteBrush.setColor(Qt::white);
    QPen whitePen;
    whitePen.setColor(Qt::white);

    QGraphicsRectItem* line = new QGraphicsRectItem();
    coord = toViewCoord(0, 0);
    line->setRect(coord[0], coord[1], gridworld->getWidth() * blockSize, blockSize);
    line->setBrush(whiteBrush);
    line->setPen(whitePen);
    scene->addItem(line);

    line = new QGraphicsRectItem();
    coord = toViewCoord(0, 1);
    line->setRect(coord[0], coord[1], blockSize, (goalY - 1) * blockSize - 1);
    line->setBrush(QBrush(white));
    line->setPen(whitePen);
    scene->addItem(line);

    line = new QGraphicsRectItem();
    coord = toViewCoord(gridworld->getWidth() - 1, 1);
    line->setRect(coord[0], coord[1], blockSize, (goalY - 1) * blockSize - 1);
    line->setBrush(QBrush(white));
    line->setPen(whitePen);
    scene->addItem(line);

    int goalY2 = goalY + 2 * goalsize - gridworld->getHeight() % 2;
    coord = toViewCoord(0, goalY2);
    line = new QGraphicsRectItem();
    line->setRect(coord[0], coord[1], blockSize, (goalY - 1) * blockSize);
    line->setBrush(QBrush(white));
    line->setPen(whitePen);
    scene->addItem(line);

    line = new QGraphicsRectItem();
    coord = toViewCoord(gridworld->getWidth() - 1, goalY2);
    line->setRect(coord[0], coord[1], blockSize, (goalY - 1) * blockSize);
    line->setBrush(QBrush(white));
    line->setPen(whitePen);
    scene->addItem(line);

    line = new QGraphicsRectItem();
    coord = toViewCoord(0, gridworld->getHeight() - 1);
    line->setRect(coord[0], coord[1], gridworld->getWidth() * blockSize, blockSize);
    line->setBrush(QBrush(white));
    line->setPen(whitePen);
    scene->addItem(line);

    score = new GridworldView_Score(this);

    scene->addItem(score);

    draw();

    //timer.start(1000.0 / 60.0);
}

Gridworld *GridworldView::getWorld()
{
    return gridworld;
}

void GridworldView::draw(){
    //qDebug() << "Drawing";
    vector<array<int, 2>> gw_agents = gridworld->getBlueTeam();
    //qDebug() << "Blue team" << gw_agents.size();
    for(unsigned i = 0; i < blueteam.size(); i++){
        array<int, 2> gw_a = gw_agents.at(i);
        //qDebug() << "Blue team" << gw_a[0] << gw_a[1];
        array<int, 2> viewCoord = toViewCoord(gw_a[0], gw_a[1]);
        //blueteam.at(i)->setPos(viewCoord[0], viewCoord[1]);
        blueteam.at(i)->setRect(viewCoord[0], viewCoord[1], blockSize, blockSize);
    }

    gw_agents = gridworld->getRedTeam();
    //qDebug() << "Red team" << gw_agents.size();
    for(unsigned i = 0; i < redteam.size(); i++){
        array<int, 2> gw_a = gw_agents.at(i);
        //qDebug() << "Red team" << gw_agents.size();
        array<int, 2> viewCoord = toViewCoord(gw_a[0], gw_a[1]);
        //redteam.at(i)->setPos(viewCoord[0], viewCoord[1]);
        redteam.at(i)->setRect(viewCoord[0], viewCoord[1], blockSize, blockSize);
    }

    array<int, 2> ballcoords = gridworld->getBallCoord();
    array<int, 2> coord = toViewCoord(ballcoords[0], ballcoords[1]);
    //qDebug() << coord[0] << coord[1];
    ball->setRect(coord[0], coord[1], blockSize, blockSize);

    score->update();
}


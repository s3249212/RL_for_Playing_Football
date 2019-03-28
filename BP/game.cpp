#include "game.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>

Game::Game(QWidget* parent)
{
    //create a scene
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setBackgroundBrush(QBrush(QImage(":/images/field.png").scaled(800,600)));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    player = new Player();
    //player->setRect(0, 0, 100, 100);
    player->setPos(width()/2, height() - player->pixmap().height());

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //createn an item to put into the scene

    //add the item to the scene
    scene->addItem(player);

    //make player focusable

    //add a view
    //QGraphicsView* view = new QGraphicsView(scene);

    score = new Score();
    scene->addItem(score);

    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);


    //spawn enemies
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(2000);

    //play background music
    /*QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/football_ambience.wav"));
    music->play();*/
}



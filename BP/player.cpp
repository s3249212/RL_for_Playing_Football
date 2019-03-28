#include "player.h"
#include "bullet.h"
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include "enemy.h"

void Player::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Left:
        if(x() >= 0){
            setPos(x() - 10, y());
        }
        break;
    case Qt::Key_Right:
        if(x() + pixmap().width() <= 800){
            setPos(x() + 10, y());
        }
        break;
    case Qt::Key_Space:
        //create a bullet
        Bullet* bullet = new Bullet();
        bullet->setPos(x(), y());
        qDebug() << "Bullet created";
        scene()->addItem(bullet);
        break;
    }
}

void Player::spawn(){
    //create an enemy
    Enemy* enemy = new Enemy();
    scene()->addItem(enemy);
}

Player::Player(QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/lego_khedira.png").scaled(100,100));
}

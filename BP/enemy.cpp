#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <stdlib.h>


Enemy::Enemy(QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/neuer.png").scaled(100,100));
    setTransformOriginPoint(50,50);
    setRotation(180);

    int random_number = rand()%700;
    setPos(random_number, 0);
    //connect
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Enemy::move(){
    setPos(x(), y() + 5);
    if(y() > 600){
        scene()->removeItem(this);
        delete this;

        //qDebug() << "Enemy deleted";
    }
}

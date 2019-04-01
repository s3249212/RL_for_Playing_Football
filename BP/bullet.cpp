#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"
#include <typeinfo>



Bullet::Bullet(QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent){
    // draw graphics
    setPixmap(QPixmap(":/images/ball.png").scaled(50, 50));
    //connect
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Bullet::move(){
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Enemy)){
            // increase the score

            // remove them both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // delete them both
            delete colliding_items[i];
            delete this;
            return;
        }
    }
    setPos(x(), y() - 10);
    if(y() + pixmap().height() < 0){
        scene()->removeItem(this);
        delete this;
        qDebug() << "Bullet deleted";
    }
}

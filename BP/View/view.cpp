#define USEQT 0
#if USEQT == 1
#include "view.h"

#include <QDebug>

View::View(QWidget *parent):
QGraphicsView(parent)
{

}

void View::setRendering(bool boolean){
    render = boolean;
}

/*void View::update(){
    //qDebug() << "Calling update.................................................";
    if(render){
        draw();
    }
}*/
#endif

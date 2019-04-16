#include "view.h"

#include <QDebug>

void View::setRendering(bool boolean){
    render = boolean;
}

void View::update(){
    qDebug() << "Calling update.................................................";
    if(render){
        draw();
    }
}

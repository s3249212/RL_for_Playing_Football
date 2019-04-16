#include "view2.h"

void View2::update(){
    if(render){
        view->draw();
        view->update();
    }
}

//
// Created by 김유진 on 2019-02-28.
//
include "controller.h"
include <fstream>


void MoveUp();
void MoveDown();
void MoveLeft();
void MoveRight();

void GetKeyState(){
    if(GetAsyncKeyState(VK_UP) & 0x8000){
        MoveUp();
    }
}

//
// Created by 김유진 on 2019-02-28.
//
#include <iostream>
#include "world.h"

#ifndef BACHELORPROJECT_VIEW_H
#define BACHELORPROJECT_VIEW_H

// View is responsible to present data to users
enum DisplayMode :int {
    GRID = 0
};

class View {
public:
    View(const Model &model) {
        this->model = model;
    }
    View() {}
    void SetModel(const Model &model) {
        this->model = model;
    }
    void Render() {
        std::cout << "Model Data = " << model.Data() << endl;
    }
private:
    Model model;
};

#endif //BACHELORPROJECT_VIEW_H

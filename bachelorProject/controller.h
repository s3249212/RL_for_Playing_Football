//
// Created by 김유진 on 2019-02-28.
//
#include "world.h"
#include "view.h"

#ifndef BACHELORPROJECT_CONTROLLER_H
#define BACHELORPROJECT_CONTROLLER_H

// Controller combines Model and View
class Controller {
public:
    Controller(const Model &model, const View &view) {
        this->SetModel(model);
        this->SetView(view);
    }
    void SetModel(const Model &model) {
        this->model = model;
    }
    void SetView(const View &view) {
        this->view = view;
    }
    // when application starts
    void OnLoad() {
        this->view.Render();
    }
private:
    Model model;
    View view;
};



#endif //BACHELORPROJECT_CONTROLLER_H

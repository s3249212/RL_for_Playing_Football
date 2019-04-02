#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QWidget>


class View : public QGraphicsView
{
private:
    bool render = true;

public:
    virtual void draw(){};
    void update();
    void setRendering(bool boolean);
};

#endif // VIEW_H

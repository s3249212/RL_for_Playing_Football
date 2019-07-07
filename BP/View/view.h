#if USEQT == 1
#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QWidget>


class View : public QGraphicsView
{
private:
    bool render = true;

public:
    View(QWidget* parent);
    virtual void draw(){};
    virtual void initialize(){};
    void update();
    void setRendering(bool boolean);
};

#endif // VIEW_H
#endif
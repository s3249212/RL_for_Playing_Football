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
    virtual void initialize(){};
    //void update();
    void setRendering(bool boolean);

/*public slots:
    void update();*/
};

#endif // VIEW_H

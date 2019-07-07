#if USEQT == 1
#include "gridworldview_score.h"

#include <array>
#include <QFont>

using namespace std;

GridworldView_Score::GridworldView_Score(GridworldView* view):
    view(view)
{
    array<int, 2> score = view->getWorld()->getScore();
    setPlainText(QString("Score: ") + QString::number(score[0]) + QString(" - ") + QString::number(score[1]));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));
}

void GridworldView_Score::update()
{
    array<int, 2> score = view->getWorld()->getScore();
    setPlainText(QString("Score: ") + QString::number(score[0]) + QString(" - ") + QString::number(score[1]));
}
#endif

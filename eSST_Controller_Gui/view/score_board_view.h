#ifndef SCORE_BOARD_VIEW_H
#define SCORE_BOARD_VIEW_H

#include <QWidget>

namespace Ui {
class ScoreBoardView;
}

class ScoreBoardView : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreBoardView(QWidget *parent = nullptr);
    ~ScoreBoardView();

private:
    Ui::ScoreBoardView *ui;
};

#endif // SCORE_BOARD_VIEW_H

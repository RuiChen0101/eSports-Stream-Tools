#ifndef SCORE_BOARD_VIEW_H
#define SCORE_BOARD_VIEW_H

#include "score_board/team.h"
#include "score_board/round.h"

#include <QWidget>

namespace Ui {
class ScoreBoardView;
}

class ScoreBoardView : public QWidget{
    Q_OBJECT

public:
    explicit ScoreBoardView(QWidget *parent = nullptr);
    ~ScoreBoardView();

private slots:
    void team1Update();
    void team2Update();
    void teamNameUpdate();
    void scoreBoardSettingUpdate();
    void useDoubleDigitUpdate(int);

private:
    void initialize();
    void registeFiles();
    void connectSignal();
    Ui::ScoreBoardView *ui;
    Team team1;
    Team team2;
};

#endif // SCORE_BOARD_VIEW_H

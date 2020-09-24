#include "score_board_view.h"
#include "ui_score_board_view.h"

ScoreBoardView::ScoreBoardView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreBoardView)
{
    ui->setupUi(this);
}

ScoreBoardView::~ScoreBoardView()
{
    delete ui;
}

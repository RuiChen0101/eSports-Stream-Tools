#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menubar.h"
#include "statusbar.h"

#include "view/timer_view.h"
#include "view/score_board_view.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void connectSignal();
    Ui::MainWindow *ui;
    MenuBar *menuBar;
    StatusBar *statusBar;
};
#endif // MAINWINDOW_H

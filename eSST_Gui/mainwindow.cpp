#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->timer_tab_layout->addWidget(new TimerView());
}

MainWindow::~MainWindow(){
    delete ui;
}

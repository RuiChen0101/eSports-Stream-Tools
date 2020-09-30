#include "network_view.h"
#include "ui_network_view.h"

NetworkView::NetworkView(QWidget *parent) :
    QWidget(parent), ui(new Ui::NetworkView){
    ui->setupUi(this);
}

NetworkView::~NetworkView(){
    delete ui;
}

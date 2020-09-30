#include "menubar.h"

MenuBar::MenuBar(QObject *parent):
    QObject(parent){}

void MenuBar::githubPageToggled(){
    QDesktopServices::openUrl(QUrl(githubPageUrl));
}

void MenuBar::settingToggled(){

}

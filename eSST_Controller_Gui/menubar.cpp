#include "menubar.h"
#include "file/file_manager.h"
#include "utility/system_call.h"

MenuBar::MenuBar(QObject *parent):
    QObject(parent){}

void MenuBar::githubPageToggled(){
    QDesktopServices::openUrl(QUrl(githubPageUrl));
}

void MenuBar::settingToggled(){

}

void MenuBar::showTimerFileFolderToggled(){
    SystemCall::openFolder(FileManager::inst()->getTimerFileDir());
}

void MenuBar::showScoreFileFolderToggled(){
    SystemCall::openFolder(FileManager::inst()->getScoreFileDir());
}

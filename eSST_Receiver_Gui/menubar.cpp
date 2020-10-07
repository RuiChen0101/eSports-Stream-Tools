#include "menubar.h"
#include "file/file_manager.h"
#include "utility/system_call.h"

MenuBar::MenuBar(QObject *parent):
    QObject(parent){}

void MenuBar::showFileFolderToggled(){
    SystemCall::openFolder(FileManager::inst()->getRootDir());
}

void MenuBar::githubPageToggled(){
    QDesktopServices::openUrl(QUrl(githubPageUrl));
}

void MenuBar::settingToggled(){

}

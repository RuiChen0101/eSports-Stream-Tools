#ifndef MENUBAR_H
#define MENUBAR_H

#include <QUrl>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QDesktopServices>

class MenuBar : public QObject{
    Q_OBJECT

public:
    MenuBar(QObject *parent = nullptr);
public slots:
    void githubPageToggled();
    void settingToggled();
    void showFileFolderToggled();
private:
    const QString githubPageUrl = "https://github.com/RuiChen0101/eSports-Stream-Tools";
};

#endif // MENUBAR_H

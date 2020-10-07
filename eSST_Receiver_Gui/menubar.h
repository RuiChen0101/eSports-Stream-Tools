#ifndef MENUBAR_H
#define MENUBAR_H

#include <QUrl>
#include <QString>
#include <QObject>
#include <QDesktopServices>

class MenuBar : public QObject{
    Q_OBJECT

public:
    MenuBar(QObject *parent = nullptr);
public slots:
    void showFileFolderToggled();
    void githubPageToggled();
    void settingToggled();
private:
    const QString githubPageUrl = "https://github.com/RuiChen0101/eSports-Stream-Tools";
};

#endif // MENUBAR_H

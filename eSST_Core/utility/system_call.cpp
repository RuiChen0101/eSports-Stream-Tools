#include "system_call.h"
#include <QDebug>

namespace SystemCall{
    void openFolder(QDir const &dir){
    #if defined(Q_OS_WIN)
        QProcess::startDetached("explorer.exe", QStringList() << QDir::toNativeSeparators(dir.path()));
    #elif defined(Q_OS_LINUX)
        QProcess::startDetached("nautilus", QStringList() << "--browser" << dir.path());
    #endif
    }
}

#ifndef TESTEXEC_H
#define TESTEXEC_H

#include <QList>
#include <QtTest>
#include <QString>

class TestExec{
public:
    TestExec(QObject *object, QString const &name){
        object->setObjectName(name);
        QList<QObject*>& list = testList();
        if (!TestExec::findObject(object)){
            list.append(object);
        }
    }

    static QList<QObject*>& testList(){
        static QList<QObject*> list;
        return list;
    }

    static bool findObject(QObject *object){
        QList<QObject*>& list = testList();
        if (list.contains(object)){
            return true;
        }

        foreach (QObject *test, list){
            if (test->objectName() == object->objectName()){
                return true;
            }
        }
        return false;
    }

    static int runAllTest(int argc, char *argv[]){
        int ret = 0;
        QList<QObject*>& list = testList();

        foreach (QObject *test, list){
            ret += QTest::qExec(test, argc, argv);
        }

        foreach (QObject *test, list){
            delete test;
        }

        return ret;
    }
};

#define ADD_TEST(className) static TestExec t(new className, #className);

#endif // TESTEXEC_H

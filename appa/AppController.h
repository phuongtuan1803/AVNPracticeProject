#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H
#include <memory>
#include <iostream>
#include "../common/avnDefs.h"
#include <QList>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../common/ipc/shm/shmem.h"
#include "SortFilterProxyModel.h"

class AppController  : public QObject
{
    Q_OBJECT
private:
    AppController(QObject *parent = nullptr){
    };
public:
    ~AppController(){};
    static std::shared_ptr<AppController> getInstance();

    QList<EmployeeScore> requestEmployeeScoreList();

    void init();

    QQmlContext* m_qmlcontext;
    QQmlApplicationEngine *m_engine;
    SortFilterProxyModel *m_proxyModel;

};

#endif // APPCONTROLLER_H

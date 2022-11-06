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
    AppController();

public:
    virtual ~AppController();
    static std::shared_ptr<AppController> getInstance();

    QList<EmployeeScore> requestEmployeeScoreList();

    void init();

    QQmlContext* m_qmlcontext;
    QQmlApplicationEngine *m_engine;
    SortFilterProxyModel *m_proxyModel;

    Q_INVOKABLE void remove(const int index);
    //    Q_INVOKABLE void updateItem(int id, QList<int> scorelist );
    Q_INVOKABLE void refeshItem(int id);
    Q_INVOKABLE void select(const int index);
    Q_INVOKABLE void updateSearch(const QString search_term);
};

#endif // APPCONTROLLER_H

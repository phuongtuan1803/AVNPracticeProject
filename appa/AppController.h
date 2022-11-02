#ifndef APP_A_CONTROLLER_H
#define APP_A_CONTROLLER_H

#include <vector>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "avnDefs.h"
#include "database.h"
#include "sortfilterproxymodel.h"

class AppController{

private:

    AppController(){
    };
public:
    AppController(AppController &other) = delete;
    void operator=(const AppController &) = delete;

    static AppController& getInstance()
    {
        static AppController singleton_;
        return singleton_;
    };

public:
    QQmlContext* m_qmlcontext;
    QQmlApplicationEngine *m_engine;

    void init();
    QList<EmployeeScore> requestEmployeeScoreList();
    EmployeeInfo requestEmployeeInfo(int id);
    EmployeeInfo requestEmployeeInfoAtIndex(int index);
};

#endif /*APP_A_CONTROLLER_H*/

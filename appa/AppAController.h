#ifndef APP_A_CONTROLLER_H
#define APP_A_CONTROLLER_H

#include <vector>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "avnDefs.h"
#include "database.h"
#include "sortfilterproxymodel.h"

class AppAController{

private:

    AppAController(){
    };
public:
    AppAController(AppAController &other) = delete;
    void operator=(const AppAController &) = delete;

    static AppAController& getInstance()
    {
        static AppAController singleton_;
        return singleton_;
    };

public:
    QQmlContext* m_qmlcontext;
    QQmlApplicationEngine *m_engine;

    QList<EmployeeScore> requestEmployeeScoreList(){
       return Database::getInstance().requestEmployeeScoreList();
    };

    EmployeeInfo requestEmployeeInfo(int id){
        return Database::getInstance().requestEmployeeInfo(id);

    };
};

#endif /*APP_A_CONTROLLER_H*/

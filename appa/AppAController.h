#ifndef APP_A_CONTROLLER_H
#define APP_A_CONTROLLER_H

#include <vector>
#include <QQmlContext>

#include "avnDefs.h"
#include "database.h"

class AppAController{
private:

    AppAController(){};
public:
    AppAController(AppAController &other) = delete;
    void operator=(const AppAController &) = delete;

    static AppAController& getInstance()
    {
        static AppAController singleton_;
        // if(singleton_==nullptr){
        //     singleton_ = new AppAController();
        // }
        return singleton_;
    };

public:
    QQmlContext* m_qmlcontext;
    QList<EmployeeScore> requestEmployeeScoreList(){
       return Database::getInstance().requestEmployeeScoreList();
        // return QList<EmployeeInfo>::fromVector(QVector<EmployeeInfo>::fromStdVector(m_employeeList));

    };

    EmployeeInfo requestEmployeeInfo(int id){
        return Database::getInstance().requestEmployeeInfo(id);

    };
};

#endif /*APP_A_CONTROLLER_H*/

#ifndef APP_A_CONTROLLER_H
#define APP_A_CONTROLLER_H

#include <vector>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "avnDefs.h"
#include "database.h"
#include "sortfilterproxymodel.h"
#include <QObject>

class AppController{
    Q_OBJECT
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
    void requestUpdateEmployeeInfo(int id, int asm_score, int cpp_score, int js_score, int opengl_score, int qml_score);


public slots:
   void onEmployeeInfoChanged(const EmployeeInfo& emplinfo);

};

#endif /*APP_A_CONTROLLER_H*/

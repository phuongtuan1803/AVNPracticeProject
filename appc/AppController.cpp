#include "AppController.h"
#include "employeelistmodel.h"

void AppController::init()
{
        EmployeeInfo empinfo = AppController::getInstance().requestEmployeeInfoAtIndex(0);
        AppController::getInstance().m_qmlcontext->setContextProperty("name",  empinfo.name);
        AppController::getInstance().m_qmlcontext->setContextProperty("asm_score",  empinfo.asm_score);
        AppController::getInstance().m_qmlcontext->setContextProperty("cpp_score",  empinfo.cpp_score);
        AppController::getInstance().m_qmlcontext->setContextProperty("js_score",  empinfo.js_score);
        AppController::getInstance().m_qmlcontext->setContextProperty("opengl_score",  empinfo.opengl_score);
        AppController::getInstance().m_qmlcontext->setContextProperty("qml_score",  empinfo.qml_score);

}

QList<EmployeeScore> AppController::requestEmployeeScoreList(){
   return Database::getInstance().requestEmployeeScoreList();
};

EmployeeInfo AppController::requestEmployeeInfo(int id){
    return Database::getInstance().requestEmployeeInfo(id);
};

EmployeeInfo AppController::requestEmployeeInfoAtIndex(int index){
    return Database::getInstance().requestEmployeeInfoAtIndex(index);
};

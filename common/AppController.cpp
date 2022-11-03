#include "AppController.h"
#include "employeelistmodel.h"
#include "../common/ipc/shm/shmem.h"
#include "../common/ipc/mq/mq_ac.h"

void AppController::init()
{
        // EmployeeInfo empinfo = AppController::getInstance().requestEmployeeInfoAtIndex(0);
        // AppController::getInstance().m_qmlcontext->setContextProperty("name",  empinfo.name);
        // AppController::getInstance().m_qmlcontext->setContextProperty("empid",  empinfo.id);
        // AppController::getInstance().m_qmlcontext->setContextProperty("asm_score",  empinfo.asm_score);
        // AppController::getInstance().m_qmlcontext->setContextProperty("cpp_score",  empinfo.cpp_score);
        // AppController::getInstance().m_qmlcontext->setContextProperty("js_score",  empinfo.js_score);
        // AppController::getInstance().m_qmlcontext->setContextProperty("opengl_score",  empinfo.opengl_score);
        // AppController::getInstance().m_qmlcontext->setContextProperty("qml_score",  empinfo.qml_score);

}

QList<EmployeeScore> AppController::requestEmployeeScoreList(){
    QList<EmployeeScore> retval;
    EmployeeScoreList employeeScoreList;
    Shmem::getInstance()->getEmployeeScoreList(employeeScoreList);
    for(int i = 0; i < MAX_EMP_LIST ;i++){
        if(employeeScoreList.l[i].id == 0){
            break;
        }
        retval.append(employeeScoreList.l[i]);
    }
    return retval;
//    return Database::getInstance().requestEmployeeScoreList();

};

EmployeeInfo AppController::requestEmployeeInfo(int id){
    MessageQueue::getInstance()->requestEmployeeInfo(id);
    // return Database::getInstance().requestEmployeeInfo(id);
};

EmployeeInfo AppController::requestEmployeeInfoAtIndex(int index){
    // return Database::getInstance().requestEmployeeInfoAtIndex(index);
    return EmployeeInfo();
};

void AppController::requestUpdateEmployeeInfo(int id, int asm_score, int cpp_score, int js_score, int opengl_score, int qml_score){
//    Database::getInstance().requestUpdateEmployeeInfo(id,asm_score, cpp_score,js_score,opengl_score,qml_score);
};

void AppController::onEmployeeInfoChanged(const EmployeeInfo& emplinfo){
        std::cout << "onEmployeeInfoChanged: ()" ;
        std::cout << "(" << emplinfo.id << ")" ;
        std::cout << "(" << emplinfo.asm_score << ")" ;
        std::cout << "(" << emplinfo.cpp_score << ")" ;
        std::cout << "(" << emplinfo.js_score << ")" ;
        std::cout << "(" << emplinfo.opengl_score << ")" ;
        std::cout << "(" << emplinfo.qml_score << ")" ;
        std::cout << std::endl;
        AppController::getInstance().m_qmlcontext->setContextProperty("name",  emplinfo.name);
        AppController::getInstance().m_qmlcontext->setContextProperty("empid",  emplinfo.id);
        AppController::getInstance().m_qmlcontext->setContextProperty("asm_score",  emplinfo.asm_score);
        AppController::getInstance().m_qmlcontext->setContextProperty("cpp_score",  emplinfo.cpp_score);
        AppController::getInstance().m_qmlcontext->setContextProperty("js_score",  emplinfo.js_score);
        AppController::getInstance().m_qmlcontext->setContextProperty("opengl_score",  emplinfo.opengl_score);
        AppController::getInstance().m_qmlcontext->setContextProperty("qml_score",  emplinfo.qml_score);
}


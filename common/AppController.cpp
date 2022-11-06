#include "AppController.h"
#include "employeelistmodel.h"
#include "../common/ipc/shm/shmem.h"
#include "../common/ipc/mq/mq_ac.h"


void AppController::init()
{
    m_name = "---";
    m_empid = 0;
    m_asm_score  = 0;
    m_cpp_score  = 0;
    m_js_score   = 0;
    m_opengl_score = 0;
    m_qml_score    = 0;

    emit nameChanged();
    emit asm_scoreChanged();
    emit cpp_scoreChanged();
    emit js_scoreChanged();
    emit opengl_scoreChanged();
    emit qml_scoreChanged();
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

        m_name          = emplinfo.name;
        m_empid         = emplinfo.id         ;
        m_asm_score     = emplinfo.asm_score     ;
        m_cpp_score     = emplinfo.cpp_score     ;
        m_js_score      = emplinfo.js_score      ;
        m_opengl_score  = emplinfo.opengl_score  ;
        m_qml_score     = emplinfo.qml_score     ;

        emit nameChanged();
        emit asm_scoreChanged();
        emit cpp_scoreChanged();
        emit js_scoreChanged();
        emit opengl_scoreChanged();
        emit qml_scoreChanged();

}

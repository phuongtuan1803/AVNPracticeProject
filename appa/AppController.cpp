#include "AppController.h"
#include "EmployeeInfoModel.h"
#include "EmployeeListModel.h"

std::shared_ptr<AppController> AppController::getInstance()
{

    std::cout << "AppController::getInstance" << std::endl;
    static std::shared_ptr<AppController> instance(new AppController());
    return instance;
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
}

void AppController::init()
{
    EmployeeInfoModel::getInstance().init();
    EmployeeListModel employeeListModel;
    employeeListModel.m_employeeList = AppController::getInstance()->requestEmployeeScoreList();
    m_qmlcontext->setContextProperty("employeeListModel",  &employeeListModel);

}


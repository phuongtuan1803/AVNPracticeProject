#include "AppController.h"
#include "EmployeeInfoModel.h"
#include "EmployeeListModel.h"

std::shared_ptr<AppController> AppController::getInstance()
{

    std::cout << "AppController::getInstance" << std::endl;
    static std::shared_ptr<AppController> instance(new AppController());
    return instance;
}

AppController::AppController()
{
}

AppController::~AppController()
{
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


Q_INVOKABLE void AppController::remove(const int index){
    beginRemoveRows(QModelIndex(), index, index);
    EmployeeListModel:: m_employeeList.removeAt(index);
    endRemoveRows();
}

//// AppC
//Q_INVOKABLE void EmployeeListModel::updateItem(int id, QList<int> scorelist ){
//    EmployeeInfoModel::getInstance().requestUpdateEmployeeInfo(id,scorelist[0],scorelist[1],scorelist[2],scorelist[3],scorelist[4]);
//}

Q_INVOKABLE void AppController::refeshItem(int id ){
    // Database::getInstance().loadDatabase("../rc/database.json");
    //    m_employeeList = EmployeeInfoModel::getInstance().requestEmployeeScoreList();

    QList<EmployeeScore> retval;
    EmployeeScoreList employeeScoreList;
    Shmem::getInstance()->getEmployeeScoreList(employeeScoreList);
    for(int i = 0; i < MAX_EMP_LIST ;i++){
        if(employeeScoreList.l[i].id == 0){
            break;
        }
        retval.append(employeeScoreList.l[i]);
    }
    m_employeeList =  retval;


    beginResetModel();
    AppController::getInstance()->m_qmlcontext->setContextProperty("employeeListModel",  this);

    //    EmployeeInfoModel::getInstance().m_employeeListModel = &this;
    //    EmployeeInfoModel::getInstance().employeeListModelChanged();

    AppController::getInstance()->init();
    endResetModel();
}

Q_INVOKABLE void AppController::select(const int index){
    MessageQueueA::getInstance()->requestEmployeeInfo(m_employeeList[index].id);
}

Q_INVOKABLE void AppController::updateSearch(const QString search_term){
    if(search_term == ""){
        return;
    }

    QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption | QRegularExpression::CaseInsensitiveOption;
    QRegularExpression regularExpression(search_term, options);
    m_proxyModel->setFilterRegularExpression(regularExpression);
    AppController::getInstance()->m_qmlcontext->setContextProperty("employeeFilterModel", m_proxyModel);

    //    EmployeeInfoModel::getInstance().m_employeeFilterModel = m_proxyModel;
    //    EmployeeInfoModel::getInstance().employeeFilterModelChanged();

}

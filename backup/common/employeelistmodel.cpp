#include "EmployeeListModel.h"
#include <thread>
#include "EmployeeInfoModel.h"
int EmployeeListModel::rowCount(const QModelIndex &parent) const{
    return m_employeeList.length();
}

QVariant EmployeeListModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }

    const EmployeeScore &item = m_employeeList[index.row()];

    switch (role) {
    case NameRole:
        return item.name;
        break;
    case AvgScoreRole:
        return item.score;
        break;
    default:
        return item.name;
        break;
    }
}


Q_INVOKABLE void EmployeeListModel::addItem(QString name, QList<int> scorelist ){
    EmployeeScore employeeScore;
    strncpy(employeeScore.name , name.toUtf8().data(), MAX_NAME_CHAR);
    int avgscore = 0;
    for(int i =0 ;i < scorelist.size() ; i++){
        avgscore += scorelist[i];
    }
    avgscore /= scorelist.size();
    employeeScore.score = avgscore;

    beginInsertRows(QModelIndex(), rowCount(), rowCount() );
    m_employeeList.append(employeeScore);
    endInsertRows();
}


bool EmployeeListModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid()){
        return false;
    }

    EmployeeScore &item = m_employeeList[index.row()];

    switch (role) {
    case NameRole:
        strncpy(item.name , value.toString().toUtf8().data(), MAX_NAME_CHAR);
        return true;
        break;
    case AvgScoreRole:
        item.score = value.toInt();
        return true;
        break;
    default:
        return false;
        break;
    }
}


QHash<int, QByteArray> EmployeeListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AvgScoreRole] = "score";
    return roles;
}


Q_INVOKABLE void EmployeeListModel::remove(const int index){
    beginRemoveRows(QModelIndex(), index, index);
    m_employeeList.removeAt(index);
    endRemoveRows();
}

Q_INVOKABLE void EmployeeListModel::updateItem(int id, QList<int> scorelist ){
    EmployeeInfoModel::getInstance().requestUpdateEmployeeInfo(id,scorelist[0],scorelist[1],scorelist[2],scorelist[3],scorelist[4]);
}

Q_INVOKABLE void EmployeeListModel::refeshItem(int id ){
    // Database::getInstance().loadDatabase("../rc/database.json");
    m_employeeList = EmployeeInfoModel::getInstance().requestEmployeeScoreList();
    beginResetModel();
     EmployeeInfoModel::getInstance().m_qmlcontext->setContextProperty("employeeListModel",  this);

//    EmployeeInfoModel::getInstance().m_employeeListModel = &this;
//    EmployeeInfoModel::getInstance().employeeListModelChanged();

    EmployeeInfoModel::getInstance().init();
    endResetModel();
}

Q_INVOKABLE void EmployeeListModel::select(const int index){
    EmployeeInfoModel::getInstance().requestEmployeeInfo(m_employeeList[index].id);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EmployeeInfoModel::getInstance().requestEmployeeInfo(m_employeeList[index].id); //note
    QQmlContext *context = EmployeeInfoModel::getInstance().m_qmlcontext;
}

Q_INVOKABLE void EmployeeListModel::updateSearch(const QString search_term){
    if(search_term == ""){
        return;
    }

    QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption | QRegularExpression::CaseInsensitiveOption;
    QRegularExpression regularExpression(search_term, options);
    m_proxyModel->setFilterRegularExpression(regularExpression);
    EmployeeInfoModel::getInstance().m_qmlcontext->setContextProperty("employeeFilterModel", m_proxyModel);

//    EmployeeInfoModel::getInstance().m_employeeFilterModel = m_proxyModel;
//    EmployeeInfoModel::getInstance().employeeFilterModelChanged();

}


#include "EmployeeListModel.h"

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



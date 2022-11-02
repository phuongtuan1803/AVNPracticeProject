#include "employeelistmodel.h"

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

Q_INVOKABLE void EmployeeListModel::updateItem(int id, QList<int> scorelist ){
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

Q_INVOKABLE void EmployeeListModel::select(const int index){
    EmployeeInfo employeeInfo = AppController::getInstance().requestEmployeeInfo(m_employeeList[index].id);

    QQmlContext *context = AppController::getInstance().m_qmlcontext;

    context->setContextProperty("name",  employeeInfo.name);
    context->setContextProperty("asm_score",  employeeInfo.asm_score);
    context->setContextProperty("cpp_score",  employeeInfo.cpp_score);
    context->setContextProperty("js_score",  employeeInfo.js_score);
    context->setContextProperty("opengl_score",  employeeInfo.opengl_score);
    context->setContextProperty("qml_score",  employeeInfo.qml_score);
    qDebug() << employeeInfo.name;
}

Q_INVOKABLE void EmployeeListModel::updateSearch(const QString search_term){
    if(search_term == ""){
        return;
    }

    QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption | QRegularExpression::CaseInsensitiveOption;
    QRegularExpression regularExpression(search_term, options);
    m_proxyModel->setFilterRegularExpression(regularExpression);
    AppController::getInstance().m_qmlcontext->setContextProperty("employeeFilterModel", m_proxyModel);
}

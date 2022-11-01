#ifndef EMPLOYEELISTMODEL_H
#define EMPLOYEELISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <cstring>

#define MAX_NAME_CHAR   100

class EmployeeListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    EmployeeListModel(QObject *parent = nullptr) : QAbstractListModel(parent){
//        EmployeeScore emp1
        m_employeeList.append(EmployeeScore{ .name = {'N', 'a', 'm', 'e', ' ', '1'}, .score = 1});
        m_employeeList.append(EmployeeScore{ .name = {'N', 'a', 'm', 'e', ' ', '2'}, .score = 2});
        m_employeeList.append(EmployeeScore{ .name = {'N', 'a', 'm', 'e', ' ', '3'}, .score = 3});
        m_employeeList.append(EmployeeScore{ .name = {'N', 'a', 'm', 'e', ' ', '4'}, .score = 4});
        m_employeeList.append(EmployeeScore{ .name = {'N', 'a', 'm', 'e', ' ', '5'}, .score = 5});
    };

    enum EmployeeListRoles{
        NameRole = Qt::UserRole + 1,
        AvgScoreRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return m_employeeList.length();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
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
            return QVariant();
            break;
        }
    }


    Q_INVOKABLE void addItem(QString name, QList<int> scorelist ){
        EmployeeScore employeeScore;
        strncpy(employeeScore.name , name.toUtf8().data(), MAX_NAME_CHAR);
        int avgscore = 0;
        for(int i =0 ;i < scorelist.size() ; i++){
            avgscore += scorelist[i];
        }
        avgscore /= scorelist.size();
        qDebug() << "avgscore: " << avgscore;
        employeeScore.score = avgscore;

        beginInsertRows(QModelIndex(), rowCount(), rowCount() + 1);
        m_employeeList.append(employeeScore);
        endInsertRows();
        qDebug() << "addItem << size : "<< m_employeeList.size();
    }

    Q_INVOKABLE void remove(const int index){

        beginRemoveRows(QModelIndex(), index, index);
        m_employeeList.removeAt(index);
        endRemoveRows();
    }
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override{
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
protected:
    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[AvgScoreRole] = "score";
        return roles;
    }
private:
    QList<EmployeeScore> m_employeeList;
};

#endif // EMPLOYEELISTMODEL_H

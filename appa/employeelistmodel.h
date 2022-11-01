#ifndef EMPLOYEELISTMODEL_H
#define EMPLOYEELISTMODEL_H

#include <QAbstractListModel>

#define MAX_NAME_CHAR   100

struct EmployeeScore{
    char name[MAX_NAME_CHAR];
    int score;
};

class EmployeeListModel : public QAbstractListModel
{
public:
    EmployeeListModel(QObject *parent = nullptr) : QAbstractListModel(parent){
//        EmployeeScore emp1
        m_employeeList.append(EmployeeScore{ .name = "name A", .score = 1});
        m_employeeList.append(EmployeeScore{ .name = "name B", .score = 2});
        m_employeeList.append(EmployeeScore{ .name = "name C", .score = 3});
        m_employeeList.append(EmployeeScore{ .name = "name D", .score = 4});
        m_employeeList.append(EmployeeScore{ .name = "name E", .score = 5});
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

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override{

    }
protected:
    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "Employee Name";
        roles[AvgScoreRole] = "Employee Average Score";
        return roles;
    }
private:
    QList<EmployeeScore> m_employeeList;
};

#endif // EMPLOYEELISTMODEL_H

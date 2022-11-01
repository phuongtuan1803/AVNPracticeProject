#ifndef EMPLOYEELISTMODEL_H
#define EMPLOYEELISTMODEL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QAbstractListModel>
#include <QDebug>
#include <cstring>
#include "avnDefs.h"
#include "AppAController.h"

class EmployeeListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    EmployeeListModel(QObject *parent = nullptr) : QAbstractListModel(parent){
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
        employeeScore.score = avgscore;

        beginInsertRows(QModelIndex(), rowCount(), rowCount() );
        m_employeeList.append(employeeScore);
        endInsertRows();
    }

    Q_INVOKABLE void remove(const int index){
        beginRemoveRows(QModelIndex(), index, index);
        m_employeeList.removeAt(index);
        endRemoveRows();
    }

    Q_INVOKABLE void select(const int index){
        EmployeeInfo employeeInfo = AppAController::getInstance().requestEmployeeInfo(m_employeeList[index].id);
//        strncpy(employeeInfo.name , std::string("Hello T").c_str(), MAX_NAME_CHAR);
//        employeeInfo.asm_score = 0;
//        employeeInfo.cpp_score = 1;
//        employeeInfo.js_score = 2;
//        employeeInfo.opengl_score = 3;
//        employeeInfo.qml_score = 4;


//        QQmlApplicationEngine engine;
        QQmlContext *context = AppAController::getInstance().m_qmlcontext;

        context->setContextProperty("name",  employeeInfo.name);
        context->setContextProperty("asm_score",  employeeInfo.asm_score);
        context->setContextProperty("cpp_score",  employeeInfo.cpp_score);
        context->setContextProperty("js_score",  employeeInfo.js_score);
        context->setContextProperty("opengl_score",  employeeInfo.opengl_score);
        context->setContextProperty("qml_score",  employeeInfo.qml_score);
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
    QList<EmployeeScore> m_employeeList;
protected:
    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[AvgScoreRole] = "score";
        return roles;
    }

};

#endif // EMPLOYEELISTMODEL_H

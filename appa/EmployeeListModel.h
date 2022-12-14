#ifndef EMPLOYEELISTMODEL_H
#define EMPLOYEELISTMODEL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRegularExpression>
#include <QAbstractListModel>
#include <QDebug>
#include <cstring>
#include "../common/avnDefs.h"
#include "SortFilterProxyModel.h"
#include "AppController.h"
#include "mq_a.h"
//#include "EmployeeInfoModel.h"
#include "../common/ipc/shm/shmem.h"

class EmployeeListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EmployeeListModel(QObject *parent = nullptr) : QAbstractListModel(parent){
        m_proxyModel = new SortFilterProxyModel(AppController::getInstance()->m_engine);
        m_proxyModel->setSourceModel(this);
    };
    ~EmployeeListModel(){}
    enum EmployeeListRoles{
        NameRole = Qt::UserRole + 1,
        AvgScoreRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void addItem(QString name, QList<int> scorelist );
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    QList<EmployeeScore> m_employeeList;
    SortFilterProxyModel *m_proxyModel;
    QString search_term;


    Q_INVOKABLE void remove(const int index);
    //    Q_INVOKABLE void updateItem(int id, QList<int> scorelist );
    Q_INVOKABLE void refeshItem(int id);
    Q_INVOKABLE void select(const int index);
    Q_INVOKABLE void updateSearch(const QString search_term);
};

#endif // EMPLOYEELISTMODEL_H

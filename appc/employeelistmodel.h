#ifndef EMPLOYEELISTMODEL_H
#define EMPLOYEELISTMODEL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRegularExpression>
#include "AppController.h"
#include <QAbstractListModel>
#include <QDebug>
#include <cstring>
#include "avnDefs.h"

class EmployeeListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    EmployeeListModel(QObject *parent = nullptr) : QAbstractListModel(parent){
        m_proxyModel = new SortFilterProxyModel(AppController::getInstance().m_engine);
        m_proxyModel->setSourceModel(this);
    };

    enum EmployeeListRoles{
        NameRole = Qt::UserRole + 1,
        AvgScoreRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void addItem(QString name, QList<int> scorelist );
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void remove(const int index);
    Q_INVOKABLE void select(const int index);
    Q_INVOKABLE void updateSearch(const QString search_term);

    QList<EmployeeScore> m_employeeList;
    QString search_term;
    SortFilterProxyModel *m_proxyModel;

};

#endif // EMPLOYEELISTMODEL_H

#ifndef APP_A_CONTROLLER_H
#define APP_A_CONTROLLER_H

#include <vector>
#include <QQmlContext>
#include <QQmlApplicationEngine>
//#include "EmployeeListModel.h""
#include "../common/avnDefs.h"
#include "SortFilterProxyModel.h"
#include <QObject>
#include "EmployeeListModel.h"
#include "../common/ipc/shm/shmem.h"
#include "mq_a.h"
#include <iostream>

class EmployeeInfoModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int empid READ empid NOTIFY empidChanged)
    Q_PROPERTY(int asm_score READ asm_score NOTIFY asm_scoreChanged)
    Q_PROPERTY(int cpp_score READ cpp_score NOTIFY cpp_scoreChanged)
    Q_PROPERTY(int js_score READ js_score NOTIFY js_scoreChanged)
    Q_PROPERTY(int opengl_score READ opengl_score NOTIFY opengl_scoreChanged)
    Q_PROPERTY(int qml_score READ qml_score NOTIFY qml_scoreChanged)
private:

    explicit EmployeeInfoModel(QObject *parent = nullptr){
    };
public:
    ~EmployeeInfoModel(){};
    EmployeeInfoModel(EmployeeInfoModel &other) = delete;
    void operator=(const EmployeeInfoModel &) = delete;

    static EmployeeInfoModel& getInstance()
    {
        static EmployeeInfoModel singleton_;
        return singleton_;
    };
    static EmployeeInfoModel instance;
public:
    void init();
//    QList<EmployeeScore> requestEmployeeScoreList();
//    EmployeeInfo requestEmployeeInfo(int id);
//    EmployeeInfo requestEmployeeInfoAtIndex(int index);
//    void requestUpdateEmployeeInfo(int id, int asm_score, int cpp_score, int js_score, int opengl_score, int qml_score);


    QString name(){return m_name;}
    int empid(){return m_empid;}
    int asm_score(){return m_asm_score;}
    int cpp_score(){return m_cpp_score;}
    int js_score(){return m_js_score;}
    int opengl_score(){return m_opengl_score;}
    int qml_score(){return m_qml_score;}

    QString m_name;
    int m_empid, m_asm_score, m_cpp_score, m_js_score, m_opengl_score, m_qml_score;

    void onEmployeeInfoChanged(const EmployeeInfo& emplinfo);

signals:
    void nameChanged();
    void empidChanged();
    void asm_scoreChanged();
    void cpp_scoreChanged();
    void js_scoreChanged();
    void opengl_scoreChanged();
    void qml_scoreChanged();
};

#endif /*APP_A_CONTROLLER_H*/

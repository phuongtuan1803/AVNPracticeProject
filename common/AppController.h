#ifndef APP_A_CONTROLLER_H
#define APP_A_CONTROLLER_H

#include <vector>
#include <QQmlContext>
#include <QQmlApplicationEngine>
//#include "employeelistmodel.h""
#include "avnDefs.h"
#include "database.h"
#include "sortfilterproxymodel.h"
#include <QObject>

class AppController : public QObject
{
   Q_OBJECT

//   Q_PROPERTY(EmployeeListModel employeeListModel READ employeeListModel NOTIFY employeeListModelChanged)
//   Q_PROPERTY(SortFilterProxyModel employeeFilterModel READ employeeFilterModel NOTIFY employeeFilterModelChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int empid READ empid NOTIFY empidChanged)
    Q_PROPERTY(int asm_score READ asm_score NOTIFY asm_scoreChanged)
    Q_PROPERTY(int cpp_score READ cpp_score NOTIFY cpp_scoreChanged)
    Q_PROPERTY(int js_score READ js_score NOTIFY js_scoreChanged)
    Q_PROPERTY(int opengl_score READ opengl_score NOTIFY opengl_scoreChanged)
    Q_PROPERTY(int qml_score READ qml_score NOTIFY qml_scoreChanged)
private:

    explicit AppController(QObject *parent = nullptr){
    };
public:
    ~AppController(){};
    AppController(AppController &other) = delete;
    void operator=(const AppController &) = delete;

    static AppController& getInstance()
    {
        static AppController singleton_;
        return singleton_;
    };
    static AppController instance;
public:
    QQmlContext* m_qmlcontext;
    QQmlApplicationEngine *m_engine;
    SortFilterProxyModel *m_proxyModel;

    void init();
    QList<EmployeeScore> requestEmployeeScoreList();
    EmployeeInfo requestEmployeeInfo(int id);
    EmployeeInfo requestEmployeeInfoAtIndex(int index);
    void requestUpdateEmployeeInfo(int id, int asm_score, int cpp_score, int js_score, int opengl_score, int qml_score);

//    EmployeeListModel employeeListModel(){return m_employeeListModel;}
//    SortFilterProxyModel employeeFilterModel(){return m_employeeFilterModel;}
    
    QString name(){return m_name;}
    int empid(){return m_empid;}
    int asm_score(){return m_asm_score;}
    int cpp_score(){return m_cpp_score;}
    int js_score(){return m_js_score;}
    int opengl_score(){return m_opengl_score;}
    int qml_score(){return m_qml_score;}

//    EmployeeListModel m_employeeListModel;
//    SortFilterProxyModel  m_employeeFilterModel;
    QString m_name;
    int m_empid, m_asm_score, m_cpp_score, m_js_score, m_opengl_score, m_qml_score;

   void onEmployeeInfoChanged(const EmployeeInfo& emplinfo);

signals:
//   void employeeListModelChanged();
//   void employeeFilterModelChanged();
    void nameChanged();
    void empidChanged();
    void asm_scoreChanged();
    void cpp_scoreChanged();
    void js_scoreChanged();
    void opengl_scoreChanged();
    void qml_scoreChanged();
};

#endif /*APP_A_CONTROLLER_H*/

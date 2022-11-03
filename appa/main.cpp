#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include "sortfilterproxymodel.h"
#include "../common/AppController.h"

#include "../common/employeelistmodel.h"
#include "../common/database.h"
#include "../common/avnDefs.h"
#include "../common/ipc/mq/mq_ac.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    

    QQmlContext *context = engine.rootContext();
    AppController::getInstance().m_qmlcontext = context;
    AppController::getInstance().m_engine = &engine;


    // Database::getInstance().loadDatabase("../rc/database.json");
    EmployeeListModel employeeListModel;
    employeeListModel.m_employeeList = AppController::getInstance().requestEmployeeScoreList();
    AppController::getInstance().m_qmlcontext->setContextProperty("employeeListModel",  &employeeListModel);
    AppController::getInstance().init();
    MessageQueue::getInstance()->appa_start();

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    QObject::connect(MessageQueue::getInstance(),SIGNAL(employeeInfoChanged(EmployeeInfo&)),&AppController::getInstance(),SLOT(onEmployeeInfoChanged(EmployeeInfo&)));
    engine.load(url);    
    return app.exec();
}

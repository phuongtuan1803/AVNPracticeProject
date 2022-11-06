#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include "SortFilterProxyModel.h"
#include "../common/EmployeeInfoModel.h"

#include "../common/EmployeeListModel.h"
#include "../common/database.h"
#include "../common/avnDefs.h"
#include "../common/ipc/mq/mq_ac.h"

static QObject *singletonTypeProvider(QQmlEngine *, QJSEngine *)
{
    return &EmployeeInfoModel::getInstance();
}

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
    
    qmlRegisterSingletonType<EmployeeInfoModel>("EmployeeInfoModel", 1, 0, "EmployeeInfoModel", singletonTypeProvider);

    QQmlContext *context = engine.rootContext();
    EmployeeInfoModel::getInstance().m_qmlcontext = context;
    EmployeeInfoModel::getInstance().m_engine = &engine;


    // Database::getInstance().loadDatabase("../rc/database.json");
    EmployeeListModel employeeListModel;
    employeeListModel.m_employeeList = EmployeeInfoModel::getInstance().requestEmployeeScoreList();

    engine.rootContext()->setContextProperty("app", &EmployeeInfoModel::getInstance());

     EmployeeInfoModel::getInstance().m_qmlcontext->setContextProperty("employeeListModel",  &employeeListModel);
//    EmployeeInfoModel::getInstance().m_employeeListModel = &employeeListModel;
//    EmployeeInfoModel::getInstance().employeeListModelChanged();

    EmployeeInfoModel::getInstance().init();
    MessageQueue::getInstance()->appa_start();

//    QObject::connect(MessageQueue::getInstance(),SIGNAL(employeeInfoChanged(EmployeeInfo&)),&EmployeeInfoModel::getInstance(),SLOT(onEmployeeInfoChanged(EmployeeInfo&)));
    engine.load(url);    
    return app.exec();
}

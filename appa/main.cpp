#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include "SortFilterProxyModel.h"
#include "EmployeeInfoModel.h"
#include "EmployeeListModel.h"
#include "AppController.h"
#include "../common/avnDefs.h"
#include "mq_a.h"

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
//    qmlRegisterSingletonType<AppController>("AppController", 1, 0, "AppController", singletonTypeProvider);

    QQmlContext *context = engine.rootContext();
    AppController::getInstance()->m_qmlcontext = context;
    AppController::getInstance()->m_engine = &engine;
    AppController::getInstance()->init();
    engine.rootContext()->setContextProperty("employeeinfo", &EmployeeInfoModel::getInstance());
//    engine.rootContext()->setContextProperty("app", AppController::getInstance());
    MessageQueueA::getInstance()->start_receive();
    engine.load(url);
    return app.exec();
}

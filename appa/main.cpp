#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include "sortfilterproxymodel.h"
#include "AppAController.h"

#include "employeelistmodel.h"
#include "database.h"
#include "avnDefs.h"

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
    AppAController::getInstance().m_qmlcontext = context;
    AppAController::getInstance().m_engine = &engine;

    Database::getInstance().loadDatabase("../rc/database.json");
    EmployeeListModel employeeListModel;
//    auto& employeeListModel = AppAController::getInstance().employeeListModel;
    employeeListModel.m_fullList = AppAController::getInstance().requestEmployeeScoreList();
    employeeListModel.m_employeeList = employeeListModel.m_fullList;
    context->setContextProperty("employeeListModel",  (&employeeListModel));

    context->setContextProperty("name",  " ");
    context->setContextProperty("asm_score",  -1);
    context->setContextProperty("cpp_score",  -1);
    context->setContextProperty("js_score",  -1);
    context->setContextProperty("opengl_score",  -1);
    context->setContextProperty("qml_score",  -1);




    engine.load(url);

    return app.exec();
}

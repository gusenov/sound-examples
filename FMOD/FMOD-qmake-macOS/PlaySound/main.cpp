#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "player.h"

int main(int argc, char *argv[])
{
    Player player;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto rootCtx = engine.rootContext();
    rootCtx->setContextProperty("player", &player);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url, &player](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);

        if (auto btnPlay = obj->findChild<QObject *>("btnPlay"))
            QObject::connect(btnPlay, SIGNAL(playClicked()), &player, SLOT(slotPlay()));

        if (auto btnResume = obj->findChild<QObject *>("btnResume"))
            QObject::connect(btnResume, SIGNAL(resumeClicked()), &player, SLOT(slotResume()));

        if (auto btnPause = obj->findChild<QObject *>("btnPause"))
            QObject::connect(btnPause, SIGNAL(pauseClicked()), &player, SLOT(slotPause()));

    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

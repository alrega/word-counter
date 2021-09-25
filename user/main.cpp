#include "word_rank_model.h"
#include "hist_thread_manager.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QDebug>

#pragma GCC diagnostic pop

int main(int argc, char **argv) {

    // Set custom message pattern
    // The default "%{if-category}%{category}: %{endif}%{message}"
    // Refer https://doc.qt.io/qt-5/qtglobal.html#qSetMessagePattern
    qSetMessagePattern("[%{time}][%{type}][%{appname}][%{category}] - %{message}");

    QGuiApplication::setApplicationName("Words Histogram");
    QGuiApplication::setOrganizationName("Demo");
    QGuiApplication::setOrganizationDomain("com.demo");
    QGuiApplication a(argc, argv);

    qmlRegisterType<WordRankModel>("com.demo.project", 1, 0, "WordRankModel");
    qmlRegisterType<HistThreadManager>("com.demo.project", 1, 0, "HistThreadManager");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    int result = a.exec();

    return result;
}

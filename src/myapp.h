#ifndef MYAPP_H
#define MYAPP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "mydatalogger.h"

class MyApp : public QGuiApplication
{
    Q_OBJECT
public:
    MyApp(int &argc, char **argv);
    ~MyApp();

signals:
    void startRecording();
    void stopRecording();

public slots:
    void updateModel(const QString &name, int width, int height, bool visible);

private:
    QQmlApplicationEngine m_engine;
    const QUrl url = QStringLiteral("qrc:/qml/main.qml");
    QThread *m_loggerThread;
    MyDataLogger *m_logger;
};

#endif // MYAPP_H

#include "myapp.h"
#include <QMetaObject>

MyApp::MyApp(int &argc, char **argv)
    : QGuiApplication(argc, argv)
    , m_loggerThread(nullptr)
    , m_logger(nullptr)
{
    connect(&m_engine, &QQmlApplicationEngine::objectCreated,
        this, [this](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    m_engine.load(url);

    m_loggerThread = new QThread(this);
    if (!m_loggerThread){
        qCritical("Not enough memory for logger thread!");
    }

    m_logger = new MyDataLogger();
    if (!m_logger) {
        qCritical("Not enough memory for logger!");
    } else {
        m_logger->moveToThread(m_loggerThread);
        m_loggerThread->start();
    }

    m_engine.rootContext()->setContextProperty("Logger", m_logger);

    connect(m_logger, &MyDataLogger::recordAdded, this, &MyApp::updateModel);
    m_logger->readLogFile();
}

MyApp::~MyApp()
{
    m_loggerThread->quit();
    m_loggerThread->wait();
}

void MyApp::updateModel(const QString &name, int width, int height, bool visible)
{
    QObject *object = m_engine.rootObjects()[0];
    if (object) {
        QMetaObject::invokeMethod(object, "updateModel",
                                  Q_ARG(QVariant, QVariant(name)),
                                  Q_ARG(QVariant, QVariant(width)),
                                  Q_ARG(QVariant, QVariant(height)),
                                  Q_ARG(QVariant, QVariant(visible))
                                  );
    }
}

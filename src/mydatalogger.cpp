#include "mydatalogger.h"
#include <QDebug>
#include <QFile>
#include <QTime>
#include <cstdlib>

#define MY_TIMEOUT 15000 // ms
#define FILE_NAME "log.txt"

MyDataLogger::MyDataLogger(QObject *parent)
    : QObject(parent)
    , m_data(nullptr)
    , m_timer(nullptr)
    , m_watcher(nullptr)
    , m_isLogging(false)
    , m_lastLogPos(0)
{
    m_data = new QVector<Test>;
    m_timer = new QTimer(parent);
    m_watcher = new QFileSystemWatcher(parent);
    if (!m_data || !m_timer || !m_watcher) {
        qCritical("Couldn't create logger");
    }

    connect(m_timer, &QTimer::timeout, this, &MyDataLogger::saveRecord);

    m_timer->setSingleShot(false);

    QFile f(FILE_NAME);
    QFileInfo fi(f);

    if (!m_watcher->addPath(fi.filePath())) {
        qWarning("Couldn't add the log file to the watcher.");
    }
    connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &MyDataLogger::readLogFile);
}

MyDataLogger::~MyDataLogger()
{

}

void MyDataLogger::toggleLogging()
{
    if (m_isLogging) {
        m_timer->stop();
        m_isLogging = false;
    } else {
        m_timer->start(MY_TIMEOUT);
        m_isLogging = true;
    }
}

void MyDataLogger::readLogFile()
{
    QFile logFile(FILE_NAME);
    if (!logFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't read the log file.");
        return;
    }

    QTextStream input(&logFile);
    input.seek(m_lastLogPos);
    while (!input.atEnd())
    {
        QString line = input.readLine();

        auto tmp = line.split(" ");
        Test t(tmp.at(0),
               tmp.at(1).toInt(),
               tmp.at(2).toInt(),
               (tmp.at(3).contains("true") ? true : false)
               );
        m_data->append(t);
        m_lastLogPos = input.pos();
        emit recordAdded(t.name(), t.width(), t.height(), t.isVisible());
    }
    logFile.close();
}

QString MyDataLogger::makeEntry()
{
    QString name(QTime::currentTime().toString());
    int width = std::rand();
    int height = std::rand();
    bool visible = (std::rand() % 2 == 0) ? true : false;
    QString ret(name + " " +
                QString::number(width) + " " +
                QString::number(height) + " " +
                (visible ? "true" : "false") + "\n"
                );
    return ret;
}

void MyDataLogger::checkFileWatcher(const QFile &f)
{
    if (m_watcher->files().isEmpty()) {
        QFileInfo fi(f);
        m_watcher->addPath(fi.filePath());
    }
}

void MyDataLogger::saveRecord()
{
    QFile logFile(FILE_NAME);

    checkFileWatcher(logFile);

    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qWarning("Couldn't open save file.");
        return;
    }

    if (logFile.write(makeEntry().toLocal8Bit()) == -1) {
        qWarning("Error while writting the log file.");
    }

    logFile.close();
}

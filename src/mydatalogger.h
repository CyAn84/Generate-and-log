#ifndef MYDATALOGGER_H
#define MYDATALOGGER_H

#include <QDateTime>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QThread>
#include <QTimer>

#include "test.h"

class MyDataLogger : public QObject
{
    Q_OBJECT
public:
    explicit MyDataLogger(QObject *parent = nullptr);
    ~MyDataLogger();

    Q_INVOKABLE void toggleLogging();
    Q_INVOKABLE void readLogFile();

signals:
    void recordAdded(const QString &name, int width, int height, bool visible);

private:
    QString makeEntry();
    void checkFileWatcher(const QFile &f);

    QVector<Test> *m_data;
    QTimer *m_timer;
    QFileSystemWatcher *m_watcher;
    bool m_isLogging;
    qint64 m_lastLogPos;

protected slots:
    void saveRecord();
};

#endif // MYDATALOGGER_H

#include "start_page.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>
#include "mainwindow.h"
#include "loggingcategory.h"

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QFile logFile(QDir::homePath() + "/application_log.txt");
    if (!logFile.isOpen()) {
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    }
    QTextStream out(&logFile);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    switch (type) {
    case QtDebugMsg:
        out << "DEBUG";
        break;
    case QtInfoMsg:
        out << "INFO";
        break;
    case QtWarningMsg:
        out << "WARNING";
        break;
    case QtCriticalMsg:
        out << "CRITICAL";
        break;
    case QtFatalMsg:
        out << "FATAL";
        break;
    }

    out << ": " << context.category << ": " << msg << Qt::endl;
    out.flush();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(messageHandler);
    Start_page w;
    w.show();
    int result = a.exec();

    qInstallMessageHandler(nullptr);
    QFile logFile(QDir::homePath() + "/application_log.txt");
    if (logFile.isOpen()) {
        logFile.close();
    }

    return result;
}

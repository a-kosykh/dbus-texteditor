#include "maindbusservice.h"
#include "mainwindow.h"
#include "dbusconnector.h"
#include "defs.h"

#include <QCommandLineParser>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName(Defs::appName);
    QApplication::setApplicationVersion(Defs::appVersion);

    QCommandLineParser parser;
    parser.setApplicationDescription("dbus-texteditor is a synchronised text editor. "
                                     "Text is synchronised beetween app instances in the same session via DBus. "
                                     "Needs a server to work.");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption startAsServerOption(QStringList() << "S" << "server",
            QCoreApplication::translate("main", "Start server"));
    parser.addOption(startAsServerOption);

    QCommandLineOption sessionOption(QStringList() << "s" << "session",
            QCoreApplication::translate("main", "Set session name. If not set - detached session."));
    sessionOption.setValueName("session_name");
    parser.addOption(sessionOption);

    parser.process(a);

    if (parser.isSet(startAsServerOption)) {
        MainDBusService service;
        if (service.startService()) {
            qInfo("Server started");
        }
        else {
            qWarning("Server is already running");
            return 1;
        }

        return a.exec();
    }
    else {
        qInfo("Starting client...");
        QObject obj;
        MainWindow w;
        DBusConnector *conn = nullptr;

        QString sessionName;
        if (parser.isSet(sessionOption)) {
            sessionName = parser.value(sessionOption);
            conn = new DBusConnector(sessionName, &obj);
            QObject::connect(&w, &MainWindow::currentTextChanged, conn, &DBusConnector::updateText);
            QObject::connect(conn, &DBusConnector::incomingText, &w, &MainWindow::incomingMessageSlot);
            w.setSessionName(sessionName);
        }
        else {
            w.setDetachedSessionName();
        }

        w.show();

        if (conn != nullptr) {
            if (!conn->getTextFromMaster()) {
                qWarning("Can't connect to server. Launch with \'-S\' flag.");
                return 1;
            }
        }
        return a.exec();
    }
}

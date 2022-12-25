#ifndef DBUSCONNECTOR_H
#define DBUSCONNECTOR_H

#include "dbustexteditor_adaptor.h"
#include "dbustexteditor_interface.h"

#include <QUuid>
#include <QObject>
#include <QDebug>

class DBusConnector : public QObject
{
    Q_OBJECT
public:
    enum eState {
        UiInitState,
        StartupState,
        NormalState,
        MessageProcessingState,
        ErrorState,
    };

    explicit DBusConnector(QString sessionName, QObject *parent = nullptr);
    ~DBusConnector();

    bool getTextFromMaster();

    eState state() const;
    void setState(eState value);

private slots:
    void processMessage(QString uuid, QString sessionName, QString text);

public slots:
    void updateText(QString text);

signals:
    void incomingText(QString text);
    void message(QString uuid, QString sessionName, QString text);

private:
    OrgExampleDbustexteditorInterface *m_iface;
    QUuid m_uuid;
    QString m_sessionName;
    eState m_state;
};

#endif // DBUSCONNECTOR_H

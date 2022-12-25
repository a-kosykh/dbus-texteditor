#include "dbusconnector.h"

DBusConnector::DBusConnector(QString sessionName, QObject *parent)
    : QObject{parent}
{
    new DbustexteditorAdaptor(this);

    QDBusConnection::sessionBus().registerObject("/", this);

    m_uuid = QUuid::createUuid();
    m_sessionName = sessionName;

    m_iface = new org::example::dbustexteditor("org.example.dbustexteditor", "/", QDBusConnection::sessionBus(), this);
    connect(m_iface, &OrgExampleDbustexteditorInterface::updatedText, this, &DBusConnector::processMessage);

    setState(UiInitState);
}

DBusConnector::~DBusConnector()
{
    if (state() != ErrorState) {
        m_iface->call("deleteConnection", m_uuid.toString(), m_sessionName);
    }
}

bool DBusConnector::getTextFromMaster()
{
    QDBusReply<QString> reply = m_iface->call("getCurrentText", m_sessionName);
    if (reply.isValid()) {
        emit incomingText(reply.value());
        return true;
    }
    else {
        setState(ErrorState);
        return false;
    }
}

DBusConnector::eState DBusConnector::state() const
{
    return m_state;
}

void DBusConnector::setState(eState value)
{
    m_state = value;
}

void DBusConnector::processMessage(QString uuid, QString sessionName, QString text)
{
    if (QUuid(uuid) != m_uuid && m_sessionName == sessionName) {
        setState(MessageProcessingState);
        emit incomingText(text);
    }
}

void DBusConnector::updateText(QString text)
{
    switch (state()) {
    case UiInitState: {
        setState(StartupState);
        break;
    }
    case StartupState: {
        setState(NormalState);
        break;
    }
    case NormalState: {
        QDBusReply<bool> reply = m_iface->call("setSessionText", m_uuid.toString(), m_sessionName, text);
        if (reply.isValid()) {

        }
        break;
    }
    case MessageProcessingState: {
        setState(NormalState);
        break;
    }
    default:
        break;
    }
}

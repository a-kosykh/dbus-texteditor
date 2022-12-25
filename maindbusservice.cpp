#include "maindbusservice.h"

#include <QDebug>

MainDBusService::MainDBusService(QObject *parent)
    : QObject{parent}
{

}

bool MainDBusService::startService()
{
    if (!QDBusConnection::sessionBus().registerService(Defs::serviceName)) {
        return false;
    }
    if (!QDBusConnection::sessionBus().registerObject(Defs::rootObjectPath, this)) {
        QDBusConnection::sessionBus().unregisterService(Defs::serviceName);
        return false;
    }

    new DbustexteditorAdaptor(this);
    m_iface = new org::example::dbustexteditor(QString(), Defs::rootObjectPath, QDBusConnection::sessionBus(), this);

    return true;
}

QString MainDBusService::getCurrentText(QString sessionName)
{
    return m_sessionTextMap.value(sessionName).second;
}

bool MainDBusService::setSessionText(QString senderUuid, QString sessionName, QString text)
{
    auto el = m_sessionTextMap.value(sessionName);
    el.first.insert(senderUuid);
    el.second = text;
    m_sessionTextMap.insert(sessionName, el);
    emit updatedText(senderUuid, sessionName, text);
    return true;
}

bool MainDBusService::deleteConnection(QString senderUuid, QString sessionName)
{
    auto el = m_sessionTextMap.value(sessionName);
    el.first.remove(senderUuid);
    m_sessionTextMap.insert(sessionName, el);
    if (el.first.size() == 0) {
        m_sessionTextMap.remove(sessionName);
    }
    return true;
}

#ifndef MAINDBUSSERVICE_H
#define MAINDBUSSERVICE_H

#include "dbustexteditor_adaptor.h"
#include "dbustexteditor_interface.h"

#include "defs.h"

#include <QPair>
#include <QMap>
#include <QObject>

class MainDBusService : public QObject
{
    Q_OBJECT
public:
    explicit MainDBusService(QObject *parent = nullptr);
    ~MainDBusService() {}
    bool startService();
public slots:
    QString getCurrentText(QString sessionName);
    bool setSessionText(QString senderUuid, QString sessionName, QString text);
    bool deleteConnection(QString senderUuid, QString sessionName);

signals:
    void updatedText(QString senderUuid, QString sessionName, QString text);

private:
    QMap<QString, QPair<QSet<QString>, QString>> m_sessionTextMap;
    OrgExampleDbustexteditorInterface *m_iface;
};

#endif // MAINDBUSSERVICE_H

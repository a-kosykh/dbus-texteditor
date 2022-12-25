#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbusconnector.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void incomingMessageSlot(QString text);
    void setSessionName(QString sessionName);
    void setDetachedSessionName();

private slots:
    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    DBusConnector *m_dbusConnector;

signals:
    void currentTextChanged(QString text);

};
#endif // MAINWINDOW_H

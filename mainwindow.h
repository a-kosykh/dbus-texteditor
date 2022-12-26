#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "defs.h"

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
    void setFilename(QString filename);

private slots:
    void on_textEdit_textChanged();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_File_triggered();
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    QString m_textBuffer;
    QString m_filename;
    bool saveAsFile();
    bool saveFile();
    bool openFile();
    bool m_isSaved = true;

signals:
    void currentTextChanged(QString text);

};
#endif // MAINWINDOW_H

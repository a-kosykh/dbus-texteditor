#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("dbus-texteditor");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::incomingMessageSlot(QString text)
{
    ui->textEdit->setText(text);
}

void MainWindow::setSessionName(QString sessionName)
{
    ui->sessionNameLabel->setText(sessionName);
}

void MainWindow::setDetachedSessionName()
{
    ui->label1->setVisible(false);
}

void MainWindow::on_textEdit_textChanged()
{
    emit currentTextChanged(ui->textEdit->toPlainText());
}

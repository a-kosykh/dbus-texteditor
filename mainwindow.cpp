#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(Defs::appName);
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

void MainWindow::setFilename(QString filename)
{
    if (m_filename != filename) {
        m_filename = filename;
        if (!m_filename.isEmpty()) {
            setWindowTitle(QString("%1 - %2").arg(Defs::appName).arg(m_filename));
        }
    }
}

void MainWindow::on_textEdit_textChanged()
{
    m_isSaved = false;
    emit currentTextChanged(ui->textEdit->toPlainText());
}

void MainWindow::on_actionSave_triggered()
{
    m_textBuffer = ui->textEdit->toPlainText();
    if (!m_filename.isEmpty()) {
        saveFile();
    }
    else {
        saveAsFile();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    m_textBuffer = ui->textEdit->toPlainText();
    saveAsFile();
}

void MainWindow::on_actionOpen_File_triggered()
{
    openFile();
}

bool MainWindow::saveAsFile()
{
    setFilename(QFileDialog::getSaveFileName(this, QObject::tr("Save file"), QDir::homePath()));
    if (m_filename.isEmpty()) {
        return false;
    }

    return saveFile();
}

bool MainWindow::saveFile()
{
    if (m_filename.isEmpty()) {
        return false;
    }

    QFile file(m_filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    stream << m_textBuffer;

    m_isSaved = true;
    return true;
}

bool MainWindow::openFile()
{
    setFilename(QFileDialog::getOpenFileName(this, QObject::tr("Open file"), QDir::homePath()));
    if (m_filename.isEmpty()) {
        return false;
    }
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    ui->textEdit->setText(file.readAll());

    m_isSaved = true;
    return true;
}


void MainWindow::on_actionExit_triggered()
{
    m_textBuffer = ui->textEdit->toPlainText();
    if (!m_isSaved) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, "Save changes?", "File has been modified, save changes?",
                                    QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (!m_filename.isEmpty()) {
                saveFile();
            }
            else {
                saveAsFile();
            }
            close();
        }
        if (reply == QMessageBox::No) {
            close();
        }
    } else {
        close();
    }
}


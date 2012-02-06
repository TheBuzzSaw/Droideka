#include "LoginWindow.h"
#include "ui_LoginWindow.h"

#include <QNetworkRequest>
#include <QFile>
#include <QTextOStream>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->playerLineEdit->setFocus();

    mNetworkAccessManager = new QNetworkAccessManager(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_playerLineEdit_returnPressed()
{
    ui->passwordLineEdit->setFocus();
}

void LoginWindow::on_loginButton_clicked()
{
    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    QNetworkRequest request;
    request.setUrl(QUrl("http://qt.nokia.com/"));

    mNetworkReply = mNetworkAccessManager->get(request);
    connect(mNetworkReply, SIGNAL(readyRead()), this, SLOT(onRead()));
}

void LoginWindow::onRead()
{
    QString response = QString(mNetworkReply->readAll().data());

    QFile file;
    file.setFileName(QString("result.txt"));
    if (file.open(QIODevice::Append))
    {
        QTextStream out(&file);
        out << response;
        file.close();
    }
}

void LoginWindow::finished(QNetworkReply *networkReply)
{
    QMessageBox box;
    box.setInformativeText(QString("Download is done!"));
    box.exec();

    networkReply->deleteLater();
}

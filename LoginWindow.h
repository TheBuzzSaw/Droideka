#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    
private slots:
    void on_playerLineEdit_returnPressed();
    void on_loginButton_clicked();
    void onRead();
    void finished(QNetworkReply* networkReply);

private:
    Ui::LoginWindow* ui;
    QNetworkAccessManager* mNetworkAccessManager;
    QNetworkReply* mNetworkReply;
};

#endif

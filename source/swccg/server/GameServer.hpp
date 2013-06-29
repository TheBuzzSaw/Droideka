#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class GameServer : public QObject
{
    Q_OBJECT

public:
    GameServer(quint16 port, QObject* parent = 0);
    virtual ~GameServer();

protected slots:
    void onConnect();

private:
    QTcpServer* _server;
};

#endif

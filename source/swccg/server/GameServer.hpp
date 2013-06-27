#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class GameServer : public QObject
{
    Q_OBJECT

public:
    GameServer(QObject* parent = 0);
    virtual ~GameServer();
};

#endif

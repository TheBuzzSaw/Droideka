#include "GameServer.hpp"
#include <QDataStream>
#include <QDebug>

GameServer::GameServer(quint16 port, QObject* parent) : QObject(parent)
{
    _server = new QTcpServer(this);
    connect(_server, SIGNAL(newConnection()), SLOT(onConnect()));

    if (_server->listen(QHostAddress::Any, port))
        qDebug() << "Listening...";
}

GameServer::~GameServer()
{
    _server->close();
}

void GameServer::onConnect()
{
    qDebug() << "CONNECTED";

    QTcpSocket* socket = _server->nextPendingConnection();
    socket->waitForReadyRead();

    qDebug() << socket->bytesAvailable();

    const int MaxLength = 1024;
    char buffer[MaxLength + 1];

    qint64 byteCount = socket->read(buffer, MaxLength);
    buffer[byteCount] = 0;

    qDebug() << buffer;

    const char* response =
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html><head><title>XPG Server</title></head>"
        "<body><p>Hello, World! Text is da bomb.</p></body>"
        "</html>"
        ;

    qDebug() << socket->write(response);

    socket->waitForBytesWritten();

    socket->close();
    delete socket;
}

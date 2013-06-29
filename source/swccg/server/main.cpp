#include <QCoreApplication>
#include "GameServer.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    new GameServer(8080, &a);
    return a.exec();
}

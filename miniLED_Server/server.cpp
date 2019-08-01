#include "server.h"
#include <QTcpSocket>


Server::Server(QObject *parent)
	: QTcpServer(parent)
{

}

Server::~Server()
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
	QTcpSocket *socket = new QTcpSocket(this);
	socket->setSocketDescriptor(socketDescriptor);
	emit comingConnected(socket);
}

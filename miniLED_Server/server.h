#pragma once

#include <QTcpServer>

class Server : public QTcpServer
{
	Q_OBJECT

public:
	Server(QObject *parent);
	~Server();
signals:
	void comingConnected(QTcpSocket *);

protected:
	void incomingConnection(qintptr socketDescriptor) override;

};

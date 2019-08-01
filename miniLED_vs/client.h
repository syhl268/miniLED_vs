#pragma once

#include <QTcpSocket>
#include <net_protocol.h>

class Client : public QTcpSocket
{
	Q_OBJECT

public:
	Client(QObject *parent=nullptr,QString ip=QString("127.0.0.1"),int port=8081);
	~Client();
	void sendShowColor(QColor color);
	bool ConnectedSuccess();

private:
	TransMessage *trData;

};

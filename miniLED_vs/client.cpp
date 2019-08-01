#include "client.h"
#include <QHostAddress>
#include <QColor>
Client::Client(QObject *parent,QString ip,int port)
	: QTcpSocket(parent)
{
	this->connectToHost(QHostAddress(ip), port);
	//初始化成员变量
	trData = new TransMessage(QColor(255, 255, 255, 255));
	//发送白色背景
	sendShowColor(QColor(255, 255, 255, 255));
}

Client::~Client()
{
	delete trData;
}

void Client::sendShowColor(QColor color)
{
	trData->setColor(color);
	this->writeData((char*)trData->getAllData(), 7);
}

bool Client::ConnectedSuccess()
{
	return this->state() == QAbstractSocket::ConnectingState && this->error() == QAbstractSocket::UnknownSocketError;
}

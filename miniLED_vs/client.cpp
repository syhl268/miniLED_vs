#include "client.h"
#include <QHostAddress>
#include <QColor>
Client::Client(QObject *parent,QString ip,int port)
	: QTcpSocket(parent)
{
	this->connectToHost(QHostAddress(ip), port);
	//��ʼ����Ա����
	trData = new TransMessage(QColor(255, 255, 255, 255));
	//���Ͱ�ɫ����
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

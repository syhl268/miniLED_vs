#include "miniled_server.h"
#include <QPaintEvent>
#include <QPen>
#include <QPainter>
#include <QMutex>
#include <QTcpSocket>
#include <net_protocol.h>
miniLED_Server::miniLED_Server(QWidget *parent, int width, int height)
	: QWidget(parent)
{
	pixmap = new QPixmap(width, height);
	pixmap->fill(QColor(0, 0, 0));
	this->resize(QSize(width, height));
	server = new Server(this);
	connect(server, SIGNAL(comingConnected(QTcpSocket*)), this, SLOT(onComingConnected(QTcpSocket*)));
	server->listen(QHostAddress::Any, 8081);
}

void miniLED_Server::setPixmap(QPixmap * pixmap)
{
	this->pixmap = pixmap;
}

QPixmap * miniLED_Server::getPixmap() const
{
	return this->pixmap;
}

void miniLED_Server::setUniColor(QColor color)
{
	QMutex mutex;
	mutex.lock();
	this->pixmap->fill(color);
	mutex.unlock();
	this->update();
}

void miniLED_Server::onComingConnected(QTcpSocket * socket)
{
	this->socket = socket;
	QObject::connect(this->socket, SIGNAL(readyRead()), this, SLOT(OnSocketReadyRead()));
}

void miniLED_Server::OnSocketReadyRead()
{
	int dataSize = 1024;
	this->data = new char[dataSize];
	this->socket->read(data, dataSize);
	uchar* udata = (uchar*)data;
	TransMessage trMsg(udata);
	if(trMsg.getValid() && trMsg.getFunc()==TransMessage::DRAW_COLOR)
	{
		this->setUniColor(trMsg.getColor());
	}
	delete data;
}

void miniLED_Server::onDisconnected()
{
	if (this->socket != NULL)
		this->socket->close();
	this->server->close();
	ui.statusBar->showMessage(QString::fromLocal8Bit("本地网络已经断开！"));
}

void miniLED_Server::paintEvent(QPaintEvent *event)
{
	QPainter* painter = new QPainter(this);
	QMutex mutex;
	mutex.lock();
	if(this->pixmap!=NULL)
		painter->drawPixmap(this->rect(), *this->pixmap);
	mutex.unlock();

}

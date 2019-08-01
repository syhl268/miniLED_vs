#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_miniled_server.h"
#include "server.h"
class miniLED_Server : public QWidget
{
	Q_OBJECT

public:
	miniLED_Server(QWidget *parent = Q_NULLPTR,int width=270,int height=160);
	void setPixmap(QPixmap *pixmap);
	QPixmap* getPixmap() const;
	void setUniColor(QColor color);

public slots:
	void onComingConnected(QTcpSocket * socket);
	void OnSocketReadyRead();
	void onDisconnected();

protected:
	void paintEvent(QPaintEvent*)override;

private:
	Ui::miniLED_ServerClass ui;
	QPixmap *pixmap=NULL;
	Server *server = NULL;
	QTcpSocket *socket = NULL;
	char* data;
};

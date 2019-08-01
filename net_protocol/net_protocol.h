#pragma once

#include "net_protocol_global.h"

#include <QObject>
#include <QColor>

class NET_PROTOCOL_EXPORT net_protocol
{
public:
	net_protocol();
};

class NET_PROTOCOL_EXPORT TransMessage : public QObject
{
	Q_OBJECT

public:
	TransMessage(QObject *parent);
	~TransMessage();

public:
	enum Func { DRAW_COLOR = 0, DRAW_IMG, CLOSE };
	TransMessage(uchar* allData = nullptr);
	//³õÊ¼»¯»­ÑÕÉ« DRAW_COLOR color;
	TransMessage(QColor color);
	uchar* getAllData();
	void setFunc(Func func) { this->func = func; }
	void setWidth(int width) { this->width = width; }
	void setHeight(int height) { this->height = height; }
	void setData(uchar* data) { this->data = data; }
	void setColor(QColor color) { this->color = color; }
	//void createCheck();
	//bool CheckLastByte();
	uchar getFunc() { return this->func; }
	int getWidth() { return this->width; }
	int getHeight() { return this->height; }
	uchar* getData() { return this->data; }
	QColor getColor() { return this->color; }
	bool getValid() { return isValid; }

private:
	const uchar Head0 = 0x01;
	const uchar Head1 = 0xAA;
	Func func;
	int width, height;
	uchar* data;
	QColor color;
	bool isValid;
	//uchar check;
};

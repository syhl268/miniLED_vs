#include "qpicturebox.h"
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QMutex>
#include <QMouseEvent>
#include <QWheelEvent>
#include "globalvar.h"
//用来表示鼠标滚轮转动作用到图片尺寸改变的因数。
#ifndef _FAC_DELTA 
#define _FAC_DELTA 0.1
#define _FAC_MAX 2.0
#define _FAC_MIN 0.2
#endif // !_FAC_DELTA

QPictureBox::QPictureBox(QWidget *parent)
	: QWidget(parent)
{
	this->pixRect = this->rect();
	this->pix = new QPixmap();
	picx = rect().x();
	picy = rect().y();
	picw = rect().width();
	pich = rect().height();
	fac = 1.0;
	deltax = 0;
	deltay = 0;

}

QPictureBox::~QPictureBox()
{
}


void QPictureBox::setImage(QImage * pic)
{
	pix->convertFromImage(*pic);
}

void QPictureBox::setPixmap(QPixmap * pixmap)
{
	QMutex mutex;
	mutex.lock();
	pix = pixmap;
	qDebug() << pix->isNull();
	mutex.unlock();
}

void QPictureBox::setData(uchar * data, int width, int height)
{
	if (data == nullptr)return;
	QImage *mImage=new QImage(data, width, height, QImage::Format_RGB888);
	QMutex mutex;
	mutex.lock();
	*this->pix = QPixmap::fromImage(*mImage);
	mutex.unlock();
	update();
}

void QPictureBox::paintEvent(QPaintEvent * event)
{
	if (pix == nullptr)return;
	if (pix->isNull())return;
	QPainter *painter = new QPainter(this);
	this->pixRect.setX(this->picx+deltax);
	this->pixRect.setY(this->picy+deltay);
		//this->pixRect.setWidth(pix->width()*fac);
		//this->pixRect.setHeight(pix->height()*fac);
	this->pixRect.setWidth(this->width()*fac);
	this->pixRect.setHeight(this->height()*fac);
		

	QMutex mutex;
	mutex.lock();
	painter->drawPixmap(this->pixRect, *pix);
	mutex.unlock();
	if (isDrawMarkPoint) {
		painter->setPen(QPen(QBrush(QColor(255, 255, 0)), 10.0f));
		painter->drawPoint(this->pixRect.x() + this->pixRect.width()*globalVar.markPointFacxRD, this->pixRect.y() + this->pixRect.height()*globalVar.markPointFacyRD);
		painter->drawPoint(this->pixRect.x() + this->pixRect.width()*globalVar.markPointFacxLD, this->pixRect.y() + this->pixRect.height()*globalVar.markPointFacyLD);
		painter->drawPoint(this->pixRect.x() + this->pixRect.width()*globalVar.markPointFacxLU, this->pixRect.y() + this->pixRect.height()*globalVar.markPointFacyLU);
		painter->drawPoint(this->pixRect.x() + this->pixRect.width()*globalVar.markPointFacxRU, this->pixRect.y() + this->pixRect.height()*globalVar.markPointFacyRU);
	}

}

void QPictureBox::resizeEvent(QResizeEvent * event)
{
	const QRect curRect = this->rect();
	picw = this->width();
	pich = this->height();
	
	repaint();
}

void QPictureBox::keyPressEvent(QKeyEvent * event)
{
}

void QPictureBox::keyReleaseEvent(QKeyEvent * event)
{
}

void QPictureBox::mousePressEvent(QMouseEvent * event)
{
	pressed = true;
	prex = event->x();
	prey = event->y();

}

void QPictureBox::mouseReleaseEvent(QMouseEvent * event)
{
	pressed = false;
	this->picx += deltax;
	this->picy += deltay;
	deltax = deltay = 0;
}

void QPictureBox::mouseMoveEvent(QMouseEvent * event)
{
	if (pressed) {
		curx = event->x();
		cury = event->y();
		deltax = curx - prex;
		deltay = cury - prey;
		
		repaint();

	}
	
}

void QPictureBox::mouseDoubleClickEvent(QMouseEvent * event)
{
	int x = event->x();
	int y = event->y();
	//LU
	if (x < pixRect.x() + pixRect.width() / 2 && y < pixRect.y() + pixRect.height() / 2) {
		globalVar.markPointFacxLU = float(x - pixRect.x()) / pixRect.width();
		globalVar.markPointFacyLU = float(y - pixRect.y()) / pixRect.height();
	}
	//RU
	if (x >= pixRect.x() + pixRect.width() / 2 && y < pixRect.y() + pixRect.height() / 2) {
		globalVar.markPointFacxRU = float(x - pixRect.x()) / pixRect.width();
		globalVar.markPointFacyRU = float(y - pixRect.y()) / pixRect.height();
	}
	//RD
	if (x >= pixRect.x() + pixRect.width() / 2 && y >= pixRect.y() + pixRect.height() / 2) {
		globalVar.markPointFacxRD = float(x - pixRect.x()) / pixRect.width();
		globalVar.markPointFacyRD = float(y - pixRect.y()) / pixRect.height();
	}
	//LD
	if (x < pixRect.x() + pixRect.width() / 2 && y >= pixRect.y() + pixRect.height() / 2) {
		globalVar.markPointFacxLD = float(x - pixRect.x()) / pixRect.width();
		globalVar.markPointFacyLD = float(y - pixRect.y()) / pixRect.height();
	}

	update();
}

void QPictureBox::wheelEvent(QWheelEvent * event)
{
	//if (pressed)return;


	int delta = event->angleDelta().y();
	delta /= abs(delta);
	if (fac+delta*_FAC_DELTA >= _FAC_MIN && fac+delta*_FAC_DELTA <= _FAC_MAX) {
		fac += delta*_FAC_DELTA;
		int dx = event->x() - pixRect.x();
		int dy = event->y() - pixRect.y();
		int dxn =dx* fac;
		int dyn =dy* fac;
		deltax = dxn-dx;
		deltay = dyn - dy;
	}

	qDebug() << fac;
	update();
}



#include "direselector.h"
#include <QPainter>
#include <QMouseEvent>
#include "Util.h"
direSelector::direSelector(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);
	selectItem = 1;
	gap = 20;
	side = 60;
	padding = 0;
	begin = 0;
	image[0].load(":/pic/pic/d1.png");
	image[1].load(":/pic/pic/d2.png");
	image[2].load(":/pic/pic/d3.png");
	image[3].load(":/pic/pic/d4.png");
	rect[0] = QRect(gap / 2 + padding, gap / 2 - padding, side, side);
	rect[1] = QRect(rect[0].x() + side + gap / 2 + padding, gap / 2 - padding, side, side);
	rect[2] = QRect(rect[1].x() + side + gap / 2 + padding, gap / 2 - padding, side, side);
	rect[3] = QRect(rect[2].x() + side + gap / 2 + padding, gap / 2 - padding, side, side);
	bgcolor[0] = QColor(255, 255, 255);
	bgcolor[1] = QColor(255, 255, 255);
	bgcolor[2] = QColor(255, 255, 255);
	bgcolor[3] = QColor(255, 255, 255);
}

direSelector::~direSelector()
{
}

void direSelector::mousePressEvent(QMouseEvent *event)
{
	QPoint point(event->x(), event->y());
	int i = 0;
	for (; i < 4; i++) {
		if (PointInRect(point, QRect(rect[i].x() + begin, rect[i].y(), rect[i].width(), rect[i].height()))) {
			begin = (1-i)*(side + gap / 2);
			break;
		}
	}
	if (i == 4)return;
	emit direcNow(i);
	selectItem = i;
	bgcolor[i] = QColor(255, 255, 255);
	update();
}

void direSelector::resizeEvent(QResizeEvent *)
{
}

void direSelector::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	//painter.fillRect(QRect(this->x(),this->y(),this->width(),this->height()), QColor(255, 255, 255, 255));
	painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 5.0f));
	painter.drawRect(QRect(rect[1].x()-gap/2+5,rect[1].y()-gap/2+5,rect[1].width()+gap/2,rect[1].height()+gap/2));
	for (int i = 0; i < 4; i++) {
		QRect drawRect = QRect(rect[i].x() + begin, rect[i].y(), rect[i].width(), rect[i].height());
		if (i == selectItem) {
			drawSelection(painter, drawRect, bgcolor[i], image[i]);

		}
		else
			drawSelection(painter, drawRect, bgcolor[i], image[i]);
	}
}

void direSelector::mouseMoveEvent(QMouseEvent *event)
{
	QPoint point(event->x(), event->y());
	for (int i = 0; i < 4; i++) {
		if (PointInRect(point, QRect(rect[i].x() + begin, rect[i].y(), rect[i].width(), rect[i].height())) && i!=selectItem) {
			bgcolor[i] = QColor(0, 0, 255);
		}
		else {
			bgcolor[i] = QColor(255, 255, 255);
		}
	}

	update();
}

void direSelector::drawSelection(QPainter & painter, QRect rect, QColor bgColor, QPixmap pixmap)
{
	painter.fillRect(rect, bgColor);
	painter.drawPixmap(rect, pixmap);
}

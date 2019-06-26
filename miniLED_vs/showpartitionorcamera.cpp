#include "showpartitionorcamera.h"
#include <QPainter>
#include <QMouseEvent>
#include "Util.h"
ShowPartitionOrCamera::ShowPartitionOrCamera(QWidget *parent,State state, QSize par_size):state(state),par_size(par_size),QWidget(parent)
{
	selectItem = {0,0};
	fir = QRect(0, 0, 100, 100);
	gap = 8;
	cam_pix = new QPixmap();
	cam_pix->load(":/qss/CachedImage_1920_1080_POS3.jpg");
}

ShowPartitionOrCamera::~ShowPartitionOrCamera()
{
}

void ShowPartitionOrCamera::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	if (this->state == CAMERA) {
		if (this->cam_pix != nullptr) {
			painter.drawPixmap(QRect(0, 0, this->width(), this->height()), *(this->cam_pix));
		}
	}
	if (this->state == PARTITION) {
		painter.fillRect(QRect(0, 0, this->width(), this->height()), QColor(120, 120, 255));
		for (int i = 0; i < par_size.width(); i++) {//列
			for (int j = 0; j < par_size.height(); j++) {//行
				QRect r(fir.x() + gap / 2 + i*(fir.width() + gap / 2), fir.y() + gap / 2 + j*(fir.height() + gap / 2), fir.width(), fir.height());//begin=g/2+i(w+g/2);
				QPen pen;
				if (selectItem.first == i && selectItem.second == j) pen = QPen(QBrush(QColor(0, 0, 0)), gap/2, Qt::PenStyle::SolidLine);
				else pen = QPen(QBrush(QColor(0, 0, 0)), 2, Qt::PenStyle::DotLine);
				drawCustomRect(painter, pen, r, QString("%1-%2").arg(j + 1).arg(i + 1));
			}
		}
	}
}

void ShowPartitionOrCamera::mousePressEvent(QMouseEvent *event)
{
	QPoint point(event->x(), event->y());

	if (this->state == PARTITION) {
		for (int i = 0; i < par_size.width(); i++) {//列
			for (int j = 0; j < par_size.height(); j++) {//行
				QRect r(fir.x() + gap / 2 + i*(fir.width() + gap / 2), fir.y() + gap / 2 + j*(fir.height() + gap / 2), fir.width(), fir.height());//begin=g/2+i(w+g/2);
				if (PointInRect(point, r))selectItem = { i,j };
			}
		}
	}
	update();
}

void ShowPartitionOrCamera::drawCustomRect(QPainter & painter, QPen pen, QRect rect, QString text)
{
	painter.setPen(pen);
	painter.drawRect(rect);
	painter.drawText(QPoint(rect.x() + 30, rect.y() + 30), text);
}

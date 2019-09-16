#include "qcolorcali.h"
#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <qmath.h>
#include <QException>

QColorCali::QColorCali(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QFile file("");
	file.open(QFile::ReadOnly);
	if (file.isOpen()) {
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		this->setStyleSheet(styleSheet);
	}
	file.close();
	triangle_points[0] = QPoint();
	triangle_points[1] = QPoint();
	triangle_points[2] = QPoint();
	pixmap= new QPixmap(":/pic/pic/a.png");
	QVector<QPoint> ps(3);
	ps[0] = calcPixmapCoord(stdPoints[0], pixmap->size());
	ps[1] = calcPixmapCoord(stdPoints[0 + 1], pixmap->size());
	ps[2] = calcPixmapCoord(stdPoints[0 + 2], pixmap->size());
	QPixmap pix1 = pixmap->copy(pixmap->rect());
	drawTriangleInPixmap(&pix1, ps);
	ui.label_ColormapShow->setScaledContents(true);
	ui.label_ColormapShow->setPixmap(pix1);
	ui.tableWidget->verticalHeader()->setMinimumWidth(40);
	stdColorGroup = new QButtonGroup(this);
	stdColorGroup->addButton(ui.radioButton_sRGB, 0);
	stdColorGroup->addButton(ui.radioButton_AdobeRGB,1);
	stdColorGroup->addButton(ui.radioButton_DCI_P3, 2);
	stdColorGroup->addButton(ui.radioButton_Rec_601, 3);
	stdColorGroup->addButton(ui.radioButton_Rec_709, 4);
	stdColorGroup->addButton(ui.radioButton_Rec_2020, 5);
	stdColorGroup->addButton(ui.radioButton_PAL, 6);
	stdColorGroup->addButton(ui.radioButton_NTSC, 7);
	stdColorGroup->addButton(ui.radioButton_CustomStd,8);

	connect(stdColorGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(on_stdColorGroup_toggled(int,bool)));


}

QColorCali::~QColorCali()
{
}

QPoint QColorCali::calcPixmapCoord(QPointF coord, QSize pixmapSize)
{
	QPoint ret;
	ret.setX(qRound(coord.x()*pixmapSize.width())+59);
	ret.setY(675-qRound(coord.y()*pixmapSize.height()));
	return ret;
}

void QColorCali::drawTriangleInPixmap(QPixmap * pixmap, QVector<QPoint> triangle)
{
	QPainter painter(pixmap);
	painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 3.2));
	painter.drawPolygon(QPolygon(triangle));
	painter.save();
}

void QColorCali::on_tableWidget_ColorCoord_ItemChaged(QTableWidgetItem * item)
{
	QVector<QPoint> ps(3);
	QVector<QPointF> points(3);
	for (int i = 0; i < 3; i++) {
		QTableWidgetItem *item = ui.tableWidget_ColorCoord->item(i, 1);
		if (item != nullptr)points[i].setX(item->text().toFloat());
		item = ui.tableWidget_ColorCoord->item(i, 2);
		if (item != nullptr)points[i].setY(item->text().toFloat());
		ps[i] = calcPixmapCoord(points[i], pixmap->size());
	}
	QPixmap pix1 = pixmap->copy(pixmap->rect());
	drawTriangleInPixmap(&pix1, ps);
	ui.label_ColormapShow->setScaledContents(true);
	ui.label_ColormapShow->setPixmap(pix1);
}

void QColorCali::on_stdColorGroup_toggled(int id,bool ischecked)
{
	if (!(id >= 0 && id < 9)) throw QException();
	if (ischecked == false)return;
	//如果是自定义标准则直接返回,功能以后添加
	if (id == 8) {
		ui.tableWidget_ColorCoord->setEditTriggers(QAbstractItemView::DoubleClicked);
		return;
	}
	else {
		ui.tableWidget_ColorCoord->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
	//
	int indexOfStdPoints = id * 3;
	QVector<QPoint> ps(3);
	ps[0] = calcPixmapCoord(stdPoints[indexOfStdPoints], pixmap->size());
	ps[1] = calcPixmapCoord(stdPoints[indexOfStdPoints + 1], pixmap->size());
	ps[2] = calcPixmapCoord(stdPoints[indexOfStdPoints + 2], pixmap->size());
	QPixmap pix1=pixmap->copy(pixmap->rect());
	drawTriangleInPixmap(&pix1, ps);
	ui.label_ColormapShow->setScaledContents(true);
	ui.label_ColormapShow->setPixmap(pix1);
	for (int i = 0; i < 3; i++) {
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(stdPoints[indexOfStdPoints+i].x()));
		ui.tableWidget_ColorCoord->setItem(i, 1, item);
		item = new QTableWidgetItem(QString::number(stdPoints[indexOfStdPoints+i].y()));
		ui.tableWidget_ColorCoord->setItem(i, 2, item);

	}

}

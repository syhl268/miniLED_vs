#pragma once

#include <QDialog>
#include "ui_qcolorcali.h"
#include <QPair>
#include <QMap>

class QColorCali : public QDialog
{
	Q_OBJECT
public:
	QPointF stdPoints[27] = {
		QPointF(0.640,0.330),QPointF(0.300,0.600), QPointF(0.150,0.060), //sRGB
		QPointF(0.670,0.330),QPointF(0.210,0.710), QPointF(0.150,0.060),//AdobeRGB
		QPointF(0.680,0.320),QPointF(0.265,0.690), QPointF(0.150,0.060),//DCI-P3
		QPointF(0.708,0.292),QPointF(0.170,0.797), QPointF(0.131,0.048),//Rec.601；暂缺，用2020
		QPointF(0.708,0.292),QPointF(0.170,0.797), QPointF(0.131,0.048),//Rec.709；暂缺，用2020
		QPointF(0.708,0.292),QPointF(0.170,0.797), QPointF(0.131,0.048),//Rec.2020
		QPointF(0.708,0.292),QPointF(0.170,0.797), QPointF(0.131,0.048),//PAL暂缺
		QPointF(0.670,0.330),QPointF(0.210,0.710), QPointF(0.140,0.080),//NTSC1953；
		QPointF(0.0,0.0),QPointF(0.0,0.0),QPointF(0.0,0.0),//自定义
	};
	//QMap->("name",arrayIndexStart)
	QMap<QString, int> triangleMap;
public:
	QColorCali(QWidget *parent = Q_NULLPTR);
	~QColorCali();

	QPoint calcPixmapCoord(QPointF coord,QSize pixmapSize);
	void drawTriangleInPixmap(QPixmap *pixmap, QVector<QPoint> triangle);
	public slots:
	void on_stdColorGroup_toggled(int id,bool ischeked);
	void on_tableWidget_ColorCoord_ItemChaged(QTableWidgetItem* item);
private:
	Ui::QColorCali ui;
	QPixmap *pixmap;
	QPoint triangle_points[3];
	QButtonGroup *stdColorGroup;
};


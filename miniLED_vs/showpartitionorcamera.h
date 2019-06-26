#pragma once

#include <QWidget>
#include <QMutex>
class ShowPartitionOrCamera : public QWidget
{
	Q_OBJECT
public:
	enum State {
		PARTITION,//绘制分区
		CAMERA,//绘制Camera回传图像
	};
	
public:
	ShowPartitionOrCamera(QWidget *parent = Q_NULLPTR,State state=PARTITION,QSize size=QSize(6,2));
	~ShowPartitionOrCamera();
	void setState(State state) { this->state = state; }
	void setPar_size(QSize par_size) { this->par_size = par_size; }
	void setSelectItem(QPair<int, int> selectItem) { this->selectItem = selectItem; }
	void setPixmap(QPixmap *cam_pix) { QMutex mutex; mutex.lock(); this->cam_pix = cam_pix; mutex.unlock(); }

protected:
	void paintEvent(QPaintEvent *) override;
	void mousePressEvent(QMouseEvent *) override;

private:
	State state;
	QSize par_size;//分区的数量，QSize.x->x列，QSize.y->y行
	QPair<int, int> selectItem;//当前选定的单元格。
	QPixmap *cam_pix;//绘制的相机回传图像。
	QRect fir;
	int gap;
private:
	void drawCustomRect(QPainter &painter, QPen pen, QRect rect, QString text);//绘制单元格，并且写上它的数字标识

};

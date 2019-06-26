#pragma once

#include <QWidget>
#include <QMutex>
class ShowPartitionOrCamera : public QWidget
{
	Q_OBJECT
public:
	enum State {
		PARTITION,//���Ʒ���
		CAMERA,//����Camera�ش�ͼ��
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
	QSize par_size;//������������QSize.x->x�У�QSize.y->y��
	QPair<int, int> selectItem;//��ǰѡ���ĵ�Ԫ��
	QPixmap *cam_pix;//���Ƶ�����ش�ͼ��
	QRect fir;
	int gap;
private:
	void drawCustomRect(QPainter &painter, QPen pen, QRect rect, QString text);//���Ƶ�Ԫ�񣬲���д���������ֱ�ʶ

};

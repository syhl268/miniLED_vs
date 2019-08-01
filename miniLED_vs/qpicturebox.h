#pragma once

#include <QWidget>


class QPictureBox : public QWidget
{
	Q_OBJECT

public:
	QPictureBox(QWidget *parent=nullptr);
	~QPictureBox();

	void setImage(QImage *pic);
	void setPixmap(QPixmap *pixmap);
	QPixmap* getPixmap() { return this->pix; };
	void setData(uchar* data, int width, int height);
	void setIsDrawMarkPoints(bool isdraw) {
		this->isDrawMarkPoint = isdraw;
	}
protected:

	virtual void paintEvent(QPaintEvent *event) override;
	virtual void resizeEvent(QResizeEvent *event) override;
	virtual void keyPressEvent(QKeyEvent *event) override;
	virtual void keyReleaseEvent(QKeyEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
	virtual void wheelEvent(QWheelEvent *event);

private:

	QPixmap *pix;
	QRect pixRect;

	int picx, picy, picw, pich;
	float fac;
	bool pressed = false;
	bool isScaled = false;
	int curx, cury, prex, prey, deltax, deltay;
	int dx, dy;//锚点/鼠标当前点距离图片起点的距离。
	bool isDrawMarkPoint = false;
};

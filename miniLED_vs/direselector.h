#pragma once

#include <QWidget>


class direSelector : public QWidget
{
	Q_OBJECT

public:
	direSelector(QWidget *parent = Q_NULLPTR);
	~direSelector();

protected:
	void mousePressEvent(QMouseEvent *);
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
	void mouseMoveEvent(QMouseEvent *);

signals:
	void direcNow(int index);

private:
	QPixmap image[4];
	QRect rect[4];
	QColor bgcolor[4];
	int selectItem;
	int gap, side, padding, begin;
	void drawSelection(QPainter& painter, QRect rect, QColor bgColor, QPixmap pixmap);

};

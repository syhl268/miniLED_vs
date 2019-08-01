#ifndef PIXITEM_H
#define PIXITEM_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include <QPointF>
#include <QDragEnterEvent>
#include <QGraphicsSceneWheelEvent>
#include <QPainter>
#include <QMouseEvent>

enum Enum_ZoomState{
    NO_STATE,
    RESET,
    ZOOM_IN,
    ZOOM_OUT
};
enum Enum_ZoomTimes{
    ZOOM_IN_TIMES = 5,
    ZOOM_OUT_TIMES=-5
};

class PixItem : public QGraphicsItem
{
public:
    PixItem();
    PixItem(QPixmap *pixmap);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void setZoomState(const int &zoomState);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    int getScaleValue() const;
    void setScaleValue(const int &);
    void setPixmap(QPixmap *pixmap);
	QPixmap getPixmap();
	void setDataCpy(uchar* data,int width,int height);
	uchar* getData(int &width,int &height);
public slots:
	void on_CameraReceived(QPixmap* mPixmap);
private:
    qreal m_scaleValue;
    QPixmap *pix;
	uchar *data;
    int m_zoomState;
    bool m_isMove;
    QPointF m_startPos;
};

#endif // PIXITEM_H

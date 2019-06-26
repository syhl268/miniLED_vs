#include "pixitem.h"
#include <QDebug>
#include <math.h>
#include <qmutex.h>
#include <qmutex.h>
PixItem::PixItem()
{

}

PixItem::PixItem(QPixmap *pixmap)
{
    pix=*pixmap;
    setAcceptDrops(true);
    m_scaleValue=0;
    m_isMove=false;

}

QRectF PixItem::boundingRect() const
{
    //return QRectF(-pix.width()/2,-pix.height()/2,pix.width(),pix.height());
	return QRectF(0,0, pix.width(), pix.height());
}

void PixItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QMutex mutex;
	mutex.lock();
    painter->drawPixmap(0,0,pix);
	mutex.unlock();
}

void PixItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    setZoomState(NO_STATE);
    int scaleValue=m_scaleValue;
    if(event->delta()>0){
        scaleValue++;
    }
    else{
        scaleValue--;
    }
    if(scaleValue>ZOOM_IN_TIMES || scaleValue<ZOOM_OUT_TIMES)return;
    m_scaleValue=scaleValue;
    qreal s;
    if(m_scaleValue>0){
        s=pow(1.1,m_scaleValue);
    }else{
        s=pow(1/1.1,-m_scaleValue);
    }
    setScale(s);
    setTransformOriginPoint(event->pos().x(),event->pos().y());
}

void PixItem::setZoomState(const int &zoomState)
{
    m_zoomState=zoomState;
    if(m_zoomState==RESET){
        m_scaleValue=0;
        setScale(1);
        setTransformOriginPoint(0,0);
    }
}

void PixItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_startPos=event->pos();
    m_isMove=true;
     int scaleValue=m_scaleValue;
     if(m_zoomState==ZOOM_IN){
         scaleValue++;
     }else if(m_zoomState==ZOOM_OUT){
         scaleValue++;
     }
     if(scaleValue> ZOOM_IN_TIMES || scaleValue< ZOOM_OUT_TIMES)return;
     if(m_scaleValue!=scaleValue){
         setTransformOriginPoint(event->pos().x(),event->pos().y());
     }
     m_scaleValue=scaleValue;
     qreal s;
     if(m_scaleValue>0){
         s=pow(1.1,m_scaleValue);
     }else{
         s=pow(1/1.1,-m_scaleValue);
     }
     setScale(s);
}

void PixItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_isMove){
        QPointF point=event->pos()-m_startPos;
        moveBy(point.x(),point.y());
    }
}

void PixItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_isMove=false;
}

int PixItem::getScaleValue() const
{
    return m_scaleValue;
}

void PixItem::setScaleValue(const int &scaleValue)
{
    if(scaleValue>ZOOM_IN_TIMES || scaleValue < ZOOM_OUT_TIMES){
        return;
    }
    m_scaleValue=scaleValue;
    qreal s;
    if(m_scaleValue>0){
        s=pow(1.1,m_scaleValue);
    }else{
        s=pow(1/1.1,-m_scaleValue);
    }
    setScale(s);
}

void PixItem::setPixmap(QPixmap *pixmap)
{
	QMutex mutex;
	mutex.lock();
    this->pix=*pixmap;
	mutex.unlock();
    this->update();
}

void PixItem::on_CameraReceived(QPixmap* mPixmap)
{
    this->setPixmap(mPixmap);
}



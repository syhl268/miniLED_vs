#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <SingleCameraControl.h>
#include <QPixmap>




class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = 0);
    bool QOpen();
    bool QGrabbing();
    bool QAbort();
    bool QClose();
    bool QSetExposureTime(int expTime);
    int QGetExposureTime();
    void setPixmap(QPixmap* mpixmap);
    void QSetCallback(CameraCallback camImgProcess);
signals:
    void cameraImgReady(QPixmap* mpixmap);
private:
    QPixmap mpixmap;
};

#endif // CAMERA_H

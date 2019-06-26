#include "camera.h"

Camera::Camera(QObject *parent):QObject(parent)
{

}

bool Camera::QOpen()
{
   return Open();
}

bool Camera::QGrabbing()
{
   return Grabbing();
}

bool Camera::QAbort()
{
    return Abort();
}

bool Camera::QClose()
{
    return Close();
}

bool Camera::QSetExposureTime(int expTime)
{
    return setExposureTime(expTime);
}

int Camera::QGetExposureTime()
{
    return getExposureTime();
}

void Camera::setPixmap(QPixmap* mpixmap)
{
    this->mpixmap=*mpixmap;
    emit cameraImgReady(mpixmap);
}

void Camera::QSetCallback(CameraCallback camImgProcess)
{
    SetCallback(camImgProcess);
}

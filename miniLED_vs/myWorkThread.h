#pragma once
#include <qthread.h>
class CameraWorkerThread : public QThread
{
	Q_OBJECT
		void run() override;
};
#pragma once
#ifndef __PHOTOFILEMANAGER__
#define __PHOTOFILEMANAGER__
#endif // !__PHOTOFILEMANAGER__

#include "Util.h"
#include <opencv2/opencv.hpp>
#include <QFile>
#include <QDir>
#include <QDateTime>

class PhotoFileManager
{
public:
	enum PhotoFileType {
		PHOTO_SRC,
		PHOTO_SRC_WARP,
		PHOTO_SRC_LIGHT,
		PHOTO_DST_LIGHT,
	};

	const QString PhotoFileTypePath[4] = { "photo/photo_src/","photo/photo_src_warp","photo/photo_src_light","photo/photo_dst_light" };
	PhotoFileManager(QString mainPath="");
	~PhotoFileManager();
	void createPaths();
	void saveMatToPath(cv::Mat &mat,PhotoRGB prgb,PhotoFileType pft);
	void setMainPath(QString mainPath);
	QString getCsvFileName(PhotoRGB prgb, PhotoFileType pft);
	QString getPhotoFileName(PhotoRGB prgb,PhotoFileType pft);
	const QString getPath(PhotoFileType pft) {
		return PhotoFileTypePath[pft];
	}
	void setDateTime(const QDateTime now);
	QDateTime getDateTime()const;

private:
	QString timeString;
	QString mainPath;
	QDateTime datetime;
};


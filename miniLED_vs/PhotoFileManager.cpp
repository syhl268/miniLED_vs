#include "PhotoFileManager.h"

const QString StrPhotoRGB[6] = { "R1","R2","G1","G2","B1","B2" };

PhotoFileManager::PhotoFileManager(QString mainPath):mainPath(mainPath)
{
	createPaths();
}


PhotoFileManager::~PhotoFileManager()
{
}

void PhotoFileManager::createPaths()
{

	for (auto i : PhotoFileTypePath) {
		QDir dir;
		dir.mkpath(mainPath+i);
	}
}

void PhotoFileManager::saveMatToPath(cv::Mat & mat, PhotoRGB prgb, PhotoFileType pft)
{

	cv::imwrite(getPhotoFileName(prgb,pft).toStdString(), mat);
}

void PhotoFileManager::setMainPath(QString mainPath)
{
	mainPath = mainPath.endsWith("/") ? mainPath : mainPath + "/";
	this->mainPath = mainPath;

	for (auto i : PhotoFileTypePath) {
		QDir dir;
		dir.mkpath(mainPath + i);
	}
}

QString PhotoFileManager::getCsvFileName(PhotoRGB prgb, PhotoFileType pft)
{
	QString path = PhotoFileTypePath[pft];
	path = path.endsWith("/") ? path : path + "/";
	path = path + timeString;
	path = path.endsWith("/") ? path : path + "/";
	//QString fname = StrPhotoRGB[prgb] + "-" + QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss") + ".csv";
	QString fname = StrPhotoRGB[prgb] + "-" + datetime.toString("yyyy-MM-dd-HH-mm-ss") + ".csv";
	return mainPath+path + fname;
}

QString PhotoFileManager::getPhotoFileName(PhotoRGB prgb, PhotoFileType pft)
{
	QString path = PhotoFileTypePath[pft];
	path = path.endsWith("/") ? path : path + "/";
	path = path + timeString;
	path = path.endsWith("/") ? path : path + "/";
	QString fname = StrPhotoRGB[prgb] + "-" + datetime.toString("yyyy-MM-dd-HH-mm-ss") + ".bmp";
	//QString fname = StrPhotoRGB[prgb] +"-"+ QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss")+ ".bmp";
	return mainPath+path+fname;
}

void PhotoFileManager::setDateTime(const QDateTime now)
{
	this->datetime = now;
}

QDateTime PhotoFileManager::getDateTime() const
{
	return this->datetime;
}


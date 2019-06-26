#include "globalvar.h"
#include <QString>
#include <QCoreApplication>

QString GlobalVar::Ip("127.0.0.1");
QString GlobalVar::WorkPath(QCoreApplication::applicationDirPath());
int GlobalVar::Port = 8081;
int GlobalVar::ScreenWidth = 960;
int GlobalVar::ScreenHeight = 270;



GlobalVar::GlobalVar(QObject *parent)
	: QObject(parent)
{
}

GlobalVar::~GlobalVar()
{
}

void GlobalVar::init()
{



}

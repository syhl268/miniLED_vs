#include "globalvar.h"
#include <QString>
#include <QCoreApplication>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <func.h>
/*
QString GlobalVar::Ip("127.0.0.1");
QString GlobalVar::WorkPath(QCoreApplication::applicationDirPath());
int GlobalVar::Port = 8081;
int GlobalVar::ScreenWidth = 960;
int GlobalVar::ScreenHeight = 270;
int GlobalVar::
*/
#define _T(x) ""#x
GlobalVar::GlobalVar(QObject *parent,QString fileName)
	: QObject(parent)
{

	//WorkPath = WorkPath.endsWith("/") ? WorkPath : WorkPath + "/";
	Proto = "TCP";
	QString fname = WorkPath + fileName;
	QFile file(fname);
	QString line;
	if (!file.exists()) {
		
	}
	else 
	{
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
		QTextStream textStream(&file);
		while (!textStream.atEnd()) 
		{
			line = textStream.readLine();
			if (line.startsWith("//"))continue;
			setValue(line);
		}
		file.close();
	}

	//mura系数不能从config.txt文件中读出来，只能从修正数据文件中读出
	//先实现为给初始化
	arrayRK = new float[ScreenWidth*ScreenHeight];
	arrayGK = new float[ScreenWidth*ScreenHeight];
	arrayBK = new float[ScreenWidth*ScreenHeight];
	arrayRB = new float[ScreenWidth*ScreenHeight];
	arrayGB = new float[ScreenWidth*ScreenHeight];
	arrayBB = new float[ScreenWidth*ScreenHeight];
	facrgb = FACRK;
	fackind = K;
	photorgb = R1;
	
}

GlobalVar::~GlobalVar()
{
}

void GlobalVar::setValue(QString line)
{
	auto strKey = line.section('=', 0, 0);
	auto strValue = line.section('=', 1, 1);
	if (strKey == "Proto")Proto = strValue;
	if (strKey == "Ip")Ip = strValue;
	if (strKey == "Port")Port = strValue.toInt();
	if (strKey == "ScreenWidth")ScreenWidth = strValue.toInt();
	if (strKey == "ScreenHeight")ScreenHeight = strValue.toInt();
	if (strKey == "BoxWidth")BoxWidth = strValue.toInt();
	if (strKey == "BoxHeight")BoxHeight = strValue.toInt();
	if (strKey == "ModuleWidth")ModuleWidth = strValue.toInt();
	if (strKey == "ModuleHeight")ModuleHeight = strValue.toInt();
	if (strKey == "GapUp")GapUp = strValue.toInt();
	if (strKey == "GapDown")GapDown = strValue.toInt();
	if (strKey == "GapLeft")GapLeft = strValue.toInt();
	if (strKey == "GapRight")GapRight = strValue.toInt();
	if (strKey == "PartWidth")PartWidth = strValue.toInt();
	if (strKey == "PartHeight")PartHeight = strValue.toInt();
	if (strKey == "HoriPartNums")HoriPartNums = strValue.toInt();
	if (strKey == "VertPartNums")VertPartNums = strValue.toInt();
	if (strKey == "markPointFacxRD")markPointFacxRD = strValue.toFloat();
	if (strKey == "markPointFacyRD")markPointFacyRD = strValue.toFloat();
	if (strKey == "markPointFacxLD")markPointFacxLD = strValue.toFloat();
	if (strKey == "markPointFacyLD")markPointFacyLD = strValue.toFloat();
	if (strKey == "markPointFacxLU")markPointFacxLU = strValue.toFloat();
	if (strKey == "markPointFacyLU")markPointFacyLU = strValue.toFloat();
	if (strKey == "markPointFacxRU")markPointFacxRU = strValue.toFloat();
	if (strKey == "markPointFacyRU")markPointFacyRU = strValue.toFloat();

}
void GlobalVar::resetValue(QString fileName)
{
	//WorkPath = WorkPath.endsWith("/") ? WorkPath : WorkPath + "/";
	QString fname = WorkPath + fileName;
	QFile file(fname);
	QString *line;
	if (!file.exists()) QMessageBox::information(NULL, "错误", "找不到配置文件！", QMessageBox::Ok);
	else
	{
		while (!file.atEnd())
		{
			line = new QString(file.readLine());
			setValue(*line);
			delete line;
		}
		file.close();
	}
}
void GlobalVar::writeFile()
{
	QFile file("config.txt");
	QString line;
	if (!file.open(QIODevice::ReadWrite))return;;
	QTextStream textStream(&file);
	textStream << _T(Proto) << "=" << Proto << endl;
	textStream << _T(Ip) << "=" << Ip << endl;
	textStream << _T(Port) << "=" << Port << endl;
	textStream << _T(ScreenWidth) << "=" << ScreenWidth << endl;
	textStream << _T(ScreenHeight) << "=" << ScreenHeight << endl;
	textStream << _T(BoxWidth) << "=" << BoxWidth << endl;
	textStream << _T(BoxHeight) << "=" << BoxHeight << endl;
	textStream << _T(ModuleWidth) << "=" << ModuleWidth << endl;
	textStream << _T(ModuleHeight) << "=" << ModuleHeight << endl;
	textStream << _T(GapUp) << "=" << GapUp << endl;
	textStream << _T(GapDown) << "=" << GapDown << endl;
	textStream << _T(GapLeft) << "=" << GapLeft << endl;
	textStream << _T(GapRight) << "=" << GapRight << endl;
	textStream << _T(PartWidth) << "=" << PartWidth << endl;
	textStream << _T(PartHeight) << "=" << PartHeight << endl;
	textStream << _T(HoriPartNums) << "=" << HoriPartNums << endl;
	textStream << _T(VertPartNums) << "=" << VertPartNums << endl;
	textStream << _T(markPointFacxRD) << "=" << markPointFacxRD << endl;
	textStream << _T(markPointFacyRD) << "=" << markPointFacyRD << endl;
	textStream << _T(markPointFacxLD) << "=" << markPointFacxLD << endl;
	textStream << _T(markPointFacyLD) << "=" << markPointFacyLD << endl;
	textStream << _T(markPointFacxLU) << "=" << markPointFacxLU << endl;
	textStream << _T(markPointFacyLU) << "=" << markPointFacyLU << endl;
	textStream << _T(markPointFacxRU) << "=" << markPointFacxRU << endl;
	textStream << _T(markPointFacyRU) << "=" << markPointFacyRU << endl;
	file.close();
	
}
QString GlobalVar::getCurBmpName()
{
	QDateTime dateTime = QDateTime::currentDateTime();
	dateTime.toString("yyyy-MM-dd-hh-mm-ss");
	QString fname;

	switch (photorgb)
	{
	case R1:
		fname = "R1.bmp";
		break;
	case R2:
		fname = "R2.bmp";
		break;
	case G1:
		fname = "G1.bmp";
		break;
	case G2:
		fname = "G2.bmp";
		break;
	case B1:
		fname = "B1.bmp";
		break;
	case B2:
		fname = "B2.bmp";
		break;
	default:
		fname = "R1.bmp";
		break;
	}
	return QString(fname);
}
FacRGB GlobalVar::moveFacRGBToNext()
{
	if (facrgb == FACBB)facrgb = FACRK;
	else facrgb=FacRGB(facrgb + 1);
	return facrgb;
}
PhotoRGB GlobalVar::movePhotoRGBToNext() {
	if (photorgb == B2)photorgb = R1;
	else photorgb = PhotoRGB(photorgb + 1);
	return photorgb;
}
GlobalVar globalVar;
QTime mytime;

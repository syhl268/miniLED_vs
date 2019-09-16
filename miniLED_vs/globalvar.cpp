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
void GlobalVar::init()
{
	//ip地址、通信协议修改：网络重新初始化

	//屏幕ScreenWidth,ScreenHeight,BoxWidth,BoxHeight,ModuleWidth,ModuleHeight修改：
	//arrayRK,arrayGK,arrayBK,arrayRB,arrayGB,arrayBB都需要重新申请内存。
	if (arrayRK != nullptr)delete[] arrayRK;
	if (arrayGK != nullptr)delete[] arrayGK;
	if (arrayBK != nullptr)delete[] arrayBK;
	if (arrayRB != nullptr)delete[] arrayRB;
	if (arrayGB != nullptr)delete[] arrayGB;
	if (arrayBB != nullptr)delete[] arrayBB;
	arrayRK = arrayGK = arrayBK = arrayRB = arrayGB = arrayBB = nullptr;
	arrayRK = new float[ScreenWidth*ScreenHeight];
	arrayGK = new float[ScreenWidth*ScreenHeight];
	arrayBK = new float[ScreenWidth*ScreenHeight];
	arrayRB = new float[ScreenWidth*ScreenHeight];
	arrayGB = new float[ScreenWidth*ScreenHeight];
	arrayBB = new float[ScreenWidth*ScreenHeight];
	for (int i = 0; i < ScreenWidth*ScreenHeight; i++) {
		arrayRK[i] = 0.0;
		arrayRB[i] = 0.0;
		arrayGK[i] = 0.0;
		arrayGB[i] = 0.0;
		arrayBK[i] = 0.0;
		arrayBB[i] = 0.0;
	}
	//originLight,realLight需要重新申请内存。
	for (int i = 0; i < 6; i++) {
		if (originLight[i] != nullptr)delete[] originLight[i];
		if (realLight[i] != nullptr)delete[] realLight[i];
		originLight[i] = nullptr;
		realLight[i] = nullptr;
		originLight[i] = new int[ScreenWidth*ScreenHeight];
		realLight[i] = new float[ScreenWidth*ScreenHeight];
	}

}
GlobalVar::GlobalVar(QObject *parent,QString fileName)
	: QObject(parent)
{

	//WorkPath = WorkPath.endsWith("/") ? WorkPath : WorkPath + "/";
	Proto = "TCP";
	isOfflineTest = true;
	isOutlineGap = false;
	isAutodeleteLocalPhoto = true;

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
	init();
	firstGL = 100;
	secondGL = 80;
	facrgb = FACRK;
	fackind = K;
	photorgb = R1;
	isConnectCameraSuccess = false;
}

GlobalVar::~GlobalVar()
{
	delete arrayRK;
	delete arrayRB;
	delete arrayGK;
	delete arrayGB;
	delete arrayBK;
	delete arrayBB;
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
	if (strKey == _T(isOutlineGap))isOutlineGap = strValue.toInt();
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
	if (strKey == _T(isAutodeleteLocalPhoto))isAutodeleteLocalPhoto = strValue.toInt();
	if (strKey == _T(isOfflineTest))isOfflineTest = strValue.toInt();
	if (strKey == _T(firstGL))firstGL = strValue.toInt();
	if (strKey == _T(secondGL))secondGL = strValue.toInt();
	if (strKey == _T(WorkPath))WorkPath = strValue;
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
	textStream << _T(isOutlineGap) << "=" << isOutlineGap << endl;
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
	textStream << _T(isOfflineTest) << "=" << isOfflineTest << endl;
	textStream << _T(isAutodeleteLocalPhoto) << "=" << isAutodeleteLocalPhoto << endl;
	textStream << _T(firstGL) << "=" << firstGL << endl;
	textStream << _T(secondGL) << "=" << secondGL << endl;
	textStream << _T(WorkPath) << "=" << WorkPath << endl;
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

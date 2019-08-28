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

GlobalVar::GlobalVar(QObject *parent,QString fileName)
	: QObject(parent)
{

	//WorkPath = WorkPath.endsWith("/") ? WorkPath : WorkPath + "/";
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

	
}

GlobalVar::~GlobalVar()
{
}

void GlobalVar::setValue(QString line)
{
	auto strKey = line.section('=', 0, 0);
	auto strValue = line.section('=', 1, 1);
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
	QString allText;
	WorkPath = WorkPath.endsWith("/") ? WorkPath : WorkPath + "/";

	QFile file(WorkPath + "config.txt");
	QString line;
	QTextStream textStream(&file);
	if (file.exists()) {
		while (!file.atEnd()) 
		{
			line = textStream.readLine();
			if (line.startsWith("//")) {
				allText += (line + "\n");
			}
			else {
				auto strKey = line.section('=', 0, 0);
				auto strValue = line.section('=', 1, 1);
				if (strKey == "Ip")allText += (strKey+"="+Ip + "\n");
				if (strKey == "Port")allText+=(strKey + "="+QString::number(Port)+"\n");
				if (strKey == "ScreenWidth")allText += (strKey + "=" + QString::number(ScreenWidth) + "\n");
				if (strKey == "ScreenHeight")allText += (strKey + "=" + QString::number(ScreenHeight) + "\n");
				if (strKey == "BoxWidth")allText += (strKey + "=" + QString::number(BoxWidth) + "\n");
				if (strKey == "BoxHeight")allText += (strKey + "=" + QString::number(BoxHeight) + "\n");
				if (strKey == "ModuleWidth")allText += (strKey + "=" + QString::number(ModuleWidth) + "\n");
				if (strKey == "ModuleHeight")allText += (strKey + "=" + QString::number(ModuleHeight) + "\n");
				if (strKey == "GapUp")allText += (strKey + "=" + QString::number(GapUp) + "\n");
				if (strKey == "GapDown") allText += (strKey + "=" + QString::number(GapDown) + "\n");
				if (strKey == "GapLeft") allText += (strKey + "=" + QString::number(GapLeft) + "\n");
				if (strKey == "GapRight") allText += (strKey + "=" + QString::number(GapRight) + "\n");
				if (strKey == "PartWidth")allText += (strKey + "=" + QString::number(PartWidth) + "\n");
				if (strKey == "PartHeight")allText += (strKey + "=" + QString::number(PartHeight) + "\n");
				if (strKey == "HoriPartNums")allText += (strKey + "=" + QString::number(HoriPartNums) + "\n");
				if (strKey == "VertPartNums")allText += (strKey + "=" + QString::number(VertPartNums) + "\n");

			}
		}
	}
	file.close();
	
}
GlobalVar globalVar;
QTime mytime;

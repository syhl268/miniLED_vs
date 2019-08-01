#pragma once

#include <QObject>
#include <QTime>

class GlobalVar : public QObject
{
	Q_OBJECT

public:
	GlobalVar(QObject *parent=NULL,QString fileName="config.txt");
	~GlobalVar();

	QString Ip, WorkPath;
	int Port;
	int ScreenWidth, ScreenHeight, BoxWidth, BoxHeight, ModuleWidth, ModuleHeight;
	int GapUp, GapDown, GapLeft, GapRight;
	int PartWidth, PartHeight, HoriPartNums, VertPartNums;
	//右下角mark点所在图片的比例
	float markPointFacxRD, markPointFacyRD;
	//左下
	float markPointFacxLD, markPointFacyLD;
	//左上
	float markPointFacxLU, markPointFacyLU;
	//右上角
	float markPointFacxRU, markPointFacyRU;
	//这部分数据是由MyTableModel类管理和维护的--demura的修正数据
	float *arrayR, *arrayG, *arrayB,*arrayW;
	uchar* snapData;
	void setValue(QString line);// line: "x=y"形式
	void resetValue(QString fileName);
	void writeFile();
};
extern GlobalVar globalVar;
extern QTime mytime;
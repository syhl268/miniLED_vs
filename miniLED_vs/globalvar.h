#pragma once

#include <QObject>
#include <QTime>
#include "Util.h"
#include "PhotoFileManager.h"

class GlobalVar : public QObject
{
	Q_OBJECT

public:
	GlobalVar(QObject *parent=NULL,QString fileName="config.txt");
	~GlobalVar();
	void init();
	QString Proto;
	QString Ip, WorkPath;
	int Port;
	int ScreenWidth, ScreenHeight, BoxWidth, BoxHeight, ModuleWidth, ModuleHeight;
	bool isOutlineGap;
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
	FacRGB facrgb;
	FacKind fackind;
	PhotoRGB photorgb;
	float *arrayRK, *arrayGK, *arrayBK;
	float *arrayRB, *arrayGB, *arrayBB;
	bool isAutodeleteLocalPhoto;
	bool isOfflineTest;
	int firstGL, secondGL;
	bool isConnectCameraSuccess;
	PhotoFileManager photoFileManager;

	int *originLight[6];
	float *realLight[6];
	//int *originLightR1, *originLightR2, *originLightG1, *originLightG2, *originLightB1, *originLightB2;
	//float *realLightR1, *realLightR2, *realLightG1, *realLightG2, *realLightB1, *realLightB2;


	void setValue(QString line);// line: "x=y"形式
	void resetValue(QString fileName);
	void writeFile();
	float* getFacData(FacRGB frgb) {
		switch (frgb) {
		case FACRK:
			return arrayRK;
		case FACRB:
			return arrayRB;
		case FACGK:
			return arrayGK;
		case FACGB:
			return arrayGB;
		case FACBK:
			return arrayBK;
		case FACBB:
			return arrayBB;
		}
	}
	QString getCurBmpName();
	//RK->RB,顺序移动。
	FacRGB moveFacRGBToNext();
	PhotoRGB movePhotoRGBToNext();

};
extern GlobalVar globalVar;
extern QTime mytime;
#pragma once

#include <QObject>
#include <QTime>

enum FacKind {
	K=0,B,
};
enum FacRGB {
	FACRK=0,FACRB,FACGK,FACGB,FACBK,FACBB,
};
enum PhotoRGB {
	R1, R2, G1, G2, B1, B2
};
class GlobalVar : public QObject
{
	Q_OBJECT

public:
	GlobalVar(QObject *parent=NULL,QString fileName="config.txt");
	~GlobalVar();
	QString Proto;
	QString Ip, WorkPath;
	int Port;
	int ScreenWidth, ScreenHeight, BoxWidth, BoxHeight, ModuleWidth, ModuleHeight;
	int GapUp, GapDown, GapLeft, GapRight;
	int PartWidth, PartHeight, HoriPartNums, VertPartNums;
	//���½�mark������ͼƬ�ı���
	float markPointFacxRD, markPointFacyRD;
	//����
	float markPointFacxLD, markPointFacyLD;
	//����
	float markPointFacxLU, markPointFacyLU;
	//���Ͻ�
	float markPointFacxRU, markPointFacyRU;
	//�ⲿ����������MyTableModel������ά����--demura����������
	FacRGB facrgb;
	FacKind fackind;
	PhotoRGB photorgb;
	float *arrayRK, *arrayGK, *arrayBK;
	float *arrayRB, *arrayGB, *arrayBB;
	uchar* snapData;
	void setValue(QString line);// line: "x=y"��ʽ
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
	//RK->RB,˳���ƶ���
	FacRGB moveFacRGBToNext();
	PhotoRGB movePhotoRGBToNext();

};
extern GlobalVar globalVar;
extern QTime mytime;
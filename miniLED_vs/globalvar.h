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
	//���½�mark������ͼƬ�ı���
	float markPointFacxRD, markPointFacyRD;
	//����
	float markPointFacxLD, markPointFacyLD;
	//����
	float markPointFacxLU, markPointFacyLU;
	//���Ͻ�
	float markPointFacxRU, markPointFacyRU;
	//�ⲿ����������MyTableModel������ά����--demura����������
	float *arrayR, *arrayG, *arrayB,*arrayW;
	uchar* snapData;
	void setValue(QString line);// line: "x=y"��ʽ
	void resetValue(QString fileName);
	void writeFile();
};
extern GlobalVar globalVar;
extern QTime mytime;
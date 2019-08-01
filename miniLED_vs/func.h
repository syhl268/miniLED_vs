#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
#define AOIAPI extern "C" __declspec(dllexport)

#define ROWS 90
#define COLS 160

typedef struct Point3{
	Point LT;
	Point Center;
	Point RB;
}Point3;


int calNumCol(vector<int> y);


void calColIdx(vector<int> y, int* out);
	

void dotDetect(cv::Mat src, int p, Point3 dotMatrix[][COLS]);

	
int calGap(Point data[], int dimension);
	

void sortEveryRow(Point3 dotMatrix[][COLS], Point3 dstDotMatrix[][COLS], Size picSize);

typedef struct _Thres{
	int high;
	int middle;
	int low;
}Thres;
typedef struct _ExportInfo{
	char* strId;
	char* saveFname;
	char* time;
}ExportInfo;
//���� ���� ���� ����
typedef struct _MarkPoints{
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
}MarkPoints;

#define BYTE unsigned char
AOIAPI BYTE* Analysis(char* markPic, char* srcPic, Thres thres, float& uniform,char* strId,char* time,char* saveFName);
//���ͼƬ�����ϣ�sort��������Ȼ�󷵻ص����ĵ�һ����Ϊ5.��Ϊ���
AOIAPI BYTE* Analysis_1(char* markPic, int srcPicWidth, int srcPicHeight, BYTE* srcPicData, Thres thres, float& uniform, char* strId, char* time, char* saveFName);
//���ѡ��mark
AOIAPI BYTE* Analysis_2(char* markPic, int srcPicWidth, int srcPicHeight, BYTE* srcPicData, Thres thres, MarkPoints markpoints, float& uniform, char* strId, char* time, char* saveFNameOnline,char* saveFNameLocal);
//Draw circle on image @srcData @srcPicWidth @srcPicHeight with color @R @G @B , center @px @py and radius @radius.
AOIAPI void circleOnImg(BYTE* srcData, int srcPicWidth, int srcPicHeight, int px, int py, int radius, int R, int G, int B, int thickness);
AOIAPI BYTE* ImageHist(BYTE* data, int srcwidth, int srcheight, int srcstep, int srcchannel, int &dstwidth, int &dstheight, int& step, int &dstchannel);

AOIAPI BYTE* ImageRead(char* fname, int& width, int& height, int& step, int& channel);
AOIAPI BYTE* AOIHist(int srcPicWidth, int srcPicHeight, BYTE* srcPicData, MarkPoints markpoints, int& dstwidth, int& dstheight, int& dststep);
AOIAPI int AOIHist_1(int srcPicWidth, int srcPicHeight, BYTE* srcPicData, int ableValueMin, int ableValueMax);
AOIAPI BYTE* ImageSC(int srcPicWidth, int srcPicHeight, BYTE* srcPicData, MarkPoints markpoints, int& dstwidth, int& dstheight, int& dststep);
//������е��������ݣ�int* -> 30*COLS;	����ͼƬwidth,height,data��mark�㡣
AOIAPI int* getLightSum(int srcPicWidth, int srcPicHeight, BYTE* srcPicData, MarkPoints markpoints);
//AOIAPI int* statistic(BYTE* srcdata, int srcwidth, int srcheight);
AOIAPI Scalar getColor(int min, int max, int current);
AOIAPI Scalar getColor_1(int min, int max, int current);

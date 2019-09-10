#pragma once

#include <QImage>
#include "func.h"
#include "globalvar.h"
#define OUT
#define IN
class IntArray
{
private:
	int width;
	int height;
	int* data;
public:
	IntArray();
	IntArray(int width, int height);
	IntArray(int width, int height, int* data);
	int GetWidth();
	int GetHeight();
	void SetValue(int row, int col,int value);
	int GetValue(int row, int col);
	void fill(int globalValue);
};

class ImageAlgorithm
{

public:
	ImageAlgorithm(int targetWidth=80,int targetHeight=30);
	void setCoreResolution(int targetWidth, int targetHeight);
	//GL=100 gamma=2.8;
	bool GL_compensation(IN int* imgSrc, IN int width, IN int height, IN uchar GL, IN float gamma, OUT float *imgOut);
	 bool Curvefit22(IN int* imgSrc1,IN int width,IN int height, IN uchar GL1, IN int *imgSrc2, IN uchar GL2, OUT IntArray &a, OUT IntArray &b);
	//@para fac: fac[0]->RK,fac[1]->RB
	void CalcFacsFromSixPic(QString fnames[6],MarkPoints markpoints,int firstGL,int secondGL,float* fac[6]);
	~ImageAlgorithm();
private:

};

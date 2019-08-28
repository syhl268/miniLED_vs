#pragma once

#include <QImage>
#include "func.h"
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
	//GL=100 gamma=2.8;
	static bool GL_compensation(IN int* imgSrc,IN int width,IN int height,IN uchar GL,IN float gamma, OUT float *imgOut);
	static bool Curvefit22(IN int* imgSrc1,IN int width,IN int height, IN uchar GL1, IN int *imgSrc2, IN uchar GL2, OUT IntArray &a, OUT IntArray &b);
	static void CalcFacsFromSixPic(QString fnames[6],MarkPoints markpoints,float* fac[6]);
	~ImageAlgorithm();
};

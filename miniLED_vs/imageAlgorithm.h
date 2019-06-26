#pragma once

#include <QImage>
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
	static bool GL_compensation(IN QImage &imgSrc,IN uchar GL,IN float gamma, OUT QImage &imgOut, OUT int &target);
	static bool Curvefit22(IN QImage &imgSrc1, IN uchar GL1, IN QImage &imgSrc2, IN uchar GL2, OUT IntArray &a, OUT IntArray &b);
	~ImageAlgorithm();
};

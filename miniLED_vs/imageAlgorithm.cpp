#include "imageAlgorithm.h"
#include <qmath.h>
#include <fstream>

IntArray::IntArray() :width(0), height(0),data(NULL)
{

}

IntArray::IntArray(int width, int height):width(width),height(height),data(NULL)
{
	this->data = new int[this->width*this->height];
	memset(this->data, 0, sizeof(int)*this->width*this->height);
}

IntArray::IntArray(int width, int height, int * data):width(width),height(height)
{
	this->data = data;
}

int IntArray::GetWidth()
{
	return this->width;
}

int IntArray::GetHeight()
{
	return this->height;
}

void IntArray::SetValue(int row, int col, int value)
{
	if (row < height && col < width)
		this->data[row*width + col] = value;
}

int IntArray::GetValue(int row, int col)
{
	return this->data[row*width + col];
}

void IntArray::fill(int globalValue)
{
	if (data == NULL)return;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			SetValue(j, i, globalValue);
		}
	}
}

bool ImageAlgorithm::GL_compensation(IN int* imgSrc,IN int width,IN int height, IN uchar GL, IN float gamma, OUT float* imgOut)
{
	int target = 0;
	if (imgSrc == nullptr)return false;
	imgOut = new float[width*height];
	//深度拷贝一份数据
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imgOut[j + i*width] = imgSrc[j + i*width];
		}
	}

	target = 1000000;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int pix = imgSrc[i + j*width];
			if (pix != 0 && target > pix) {
				target = pix;
			}
		}
	}
	double d = 0, b = 0;
	float realLight = 0;
#ifdef _DEBUG
	std::ofstream outfile("输出结果.csv");
#endif
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			//QColor pix = imgSrc.pixelColor(i, j);
			int pix = imgSrc[i + j*width];
			if (pix != 0) {
				d = target;
				b = pix;
				realLight = qRound(qPow((d / b), 1.0f / gamma)*GL);
			}
			else {
				realLight = GL;
			}
#ifdef _DEBUG
			outfile << int( realLight) << ",";
#endif
			imgOut[i + j*width] = realLight;
		}
		outfile << std::endl;

	}
#ifdef _DEBUG
	outfile.close();
#endif
	return true;
}

bool ImageAlgorithm::Curvefit22(IN int * imgSrc1, IN int W, IN int H, IN uchar GL1, IN int * imgSrc2, IN uchar GL2, OUT IntArray & a, OUT IntArray & b)
{

	a = *(new IntArray(W, H));
	b = *(new IntArray(W, H));
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			int pix1 = imgSrc1[i+j*W];
			int pix2 = imgSrc2[i+j*W];
			a.SetValue(j, i, (pix1 - pix2) / (GL1 - GL2));
			b.SetValue(j, i, pix1 - a.GetValue(j, i)*GL1);
		}
	}
	return true;
}
void ImageAlgorithm::CalcFacsFromSixPic(QString fnames[6], MarkPoints markpoints,float* fac[6])
{
	int* originLight[6];
	float *realLight[6];
	Size resl = getResolution();
	int maxnum = resl.width*resl.height;
	for (int i = 0; i < 6; i++) {
		originLight[i]= getLightSum(imread(fnames[i].toStdString()), markpoints);
		realLight[i] = new float[maxnum];
		GL_compensation(originLight[i], resl.width, resl.height, 100, 2.8, realLight[i]);
	}
	//计算R的系数k和b
	
	for (int i = 0; i < maxnum; i++) {
		//RK=(Y1-Y2)/(X1-X2); 
		fac[0][i] = (realLight[0][i] - realLight[1][i]) / (originLight[0][i] - originLight[1][i]);
		//RB=Y-RK*X; real->Y  origin->X
		fac[1][i] = realLight[0][i] - fac[0][i] * originLight[0][i];
	}
	for (int i = 0; i < maxnum; i++) {
		//RK=(Y1-Y2)/(X1-X2); 
		fac[2][i] = (realLight[2][i] - realLight[3][i]) / (originLight[2][i] - originLight[3][i]);
		//RB=Y-RK*X; real->Y  origin->X
		fac[3][i] = realLight[2][i] - fac[2][i] * originLight[2][i];
	}
	for (int i = 0; i < maxnum; i++) {
		//RK=(Y1-Y2)/(X1-X2); 
		fac[4][i] = (realLight[4][i] - realLight[5][i]) / (originLight[4][i] - originLight[5][i]);
		//RB=Y-RK*X; real->Y  origin->X
		fac[5][i] = realLight[4][i] - fac[4][i] * originLight[4][i];
	}

}
ImageAlgorithm::~ImageAlgorithm()
{

}

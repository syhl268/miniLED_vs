#include "imageAlgorithm.h"
#include <qmath.h>

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

bool ImageAlgorithm::GL_compensation(IN QImage & imgSrc, IN uchar GL, IN float gamma, OUT QImage & imgOut, OUT int & target)
{
	if (&imgSrc == NULL)return false;

	imgOut = *(new QImage(imgSrc.size(),imgSrc.format()));
	imgOut.fill(QColor(0, 0, 0));
	target = 1000000;
	for (int i = 0; i < imgSrc.size().width(); i++) {
		for (int j = 0; j < imgSrc.size().height(); j++) {
			QColor pix = imgSrc.pixelColor(i, j);
			if (pix != QColor(0, 0, 0) && target > pix.red()) {
				target = pix.red();
			}
		}
	}
	int d = 0, b = 0;

	for (int i = 0; i < imgSrc.size().width(); i++) {
		for (int j = 0; j < imgSrc.size().height(); j++) {
			d = target;
			b = imgSrc.pixelColor(i, j).red();
			int realLight = qRound(qPow((d / b), 1.0f / gamma)*GL);
			imgOut.setPixelColor(i, j, qRgb(realLight, realLight, realLight));
		}
	}

	return true;
}

bool ImageAlgorithm::Curvefit22(IN QImage & imgSrc1, IN uchar GL1, IN QImage & imgSrc2, IN uchar GL2, OUT IntArray & a, OUT IntArray & b)
{
	int W = imgSrc1.size().width();
	int H = imgSrc1.size().height();
	a = *(new IntArray(W, H));
	b = *(new IntArray(W, H));
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			int pix1 = imgSrc1.pixelColor(i, j).red();
			int pix2 = imgSrc2.pixelColor(i, j).red();
			a.SetValue(j, i, (pix1 - pix2) / (GL1 - GL2));
			b.SetValue(j, i, pix1 - a.GetValue(j, i)*GL1);
		}
	}
	return true;
}

ImageAlgorithm::~ImageAlgorithm()
{

}

#pragma once
#include <QMutex>

template<class T>
class Array2D
{
public:

	Array2D(int width, int height, T uniValue) :width(width),height(height)
	{
		data = new T[width*height];
		for (int j = 0; j < height; j++)for (int i = 0; i < width; i++)data[i + j*width] = uniValue;
	}

	~Array2D() {

	}
	void set(int x, int y, T value) {
		mutex->lock();
		this->data[x + y*width] = value;
		mutex->unlock();
	}
	T get(int x, int y) {
		mutex->lock();
		return this->data[x + y*width];
		mutex->lock();
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
private:
	QMutex *mutex;
	T *data;
	int width;
	int height;

};
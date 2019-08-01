#include "mytablemodel.h"
#include <QMutex>

MyTableModel::MyTableModel(QObject *parent, QColor backColor, int col, int row, float *facData)
	: QAbstractTableModel(parent),bgColor(backColor),  row(row), col(col), facData(facData)
{
	if (facData == nullptr) {
		if (row >= 1 && col >= 1)
			this->facData = new float[row*col];
		
	}
}

MyTableModel::~MyTableModel()
{

}

Q_INVOKABLE int MyTableModel::rowCount(const QModelIndex & parent) const
{
	return this->row;
}

Q_INVOKABLE int MyTableModel::columnCount(const QModelIndex & parent) const
{
	return this->col;
}

Q_INVOKABLE QVariant MyTableModel::data(const QModelIndex & index, int role) const
{
	int i = index.column();
	int j = index.row();
	int idx = i + j*this->col;
	if (idx < 0 || idx >= this->row*this->col)
		return QVariant();

	QVariant theResult;

	switch (role) {
	case Qt::BackgroundColorRole:
		theResult= QColor(this->bgColor);
		break;
	case Qt::TextColorRole:
		theResult =QColor(0,0,0);
		break;
	case Qt::TextAlignmentRole:
		theResult = QVariant(Qt::AlignCenter);
		break;
	case Qt::DisplayRole:
		theResult = QString().sprintf("%1.3f", facData[idx]);
		break;
	case Qt::EditRole:
		theResult = QString().sprintf("%1.9f", facData[idx]);
		break;
	case Qt::CheckStateRole:
		theResult = QVariant();
		break;
		
	}
	return theResult;
}

Q_INVOKABLE bool MyTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid())return false;
	int i = index.column();
	int j = index.row();
	int idx = i + j*this->col;
	if (idx < 0 || idx >= this->row*this->col)return false;
	switch (role)
	{
	case Qt::DisplayRole:
	case Qt::EditRole:
		this->facData[idx] = value.toFloat();
		break;
	default:
		break;
	}
	return true;
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())return Qt::ItemIsEnabled;
	return QAbstractItemModel::flags(index)|Qt::ItemIsEditable;
}

bool MyTableModel::alterData(const QModelIndex & index, char alterType, float deltaValue)
{

	if (!index.isValid())return false;

	int i = index.column();
	int j = index.row();
	int idx = i + j*this->col;
	if (idx < 0 || idx >= this->row*this->col)return false;


	QMutex mutex;
	mutex.lock();
	switch (alterType) {
	case '+':
		facData[idx] += deltaValue;
		break;
	case '-':
		facData[idx] -= deltaValue;
		break;
	case '*':
		facData[idx] *= deltaValue;
		break;
	case '/':
		facData[idx] /= deltaValue;
		break;

	}
	mutex.unlock();
	return true;
}

void MyTableModel::resetData()
{
	//reset code

}

void MyTableModel::setFacData(int col,int row,float *facData)
{
	QMutex mutex;
	mutex.lock();
	this->col = col;
	this->row = row;
	this->facData = facData;
	mutex.unlock();
}

void MyTableModel::setBgColor(QColor color)
{
	this->bgColor = color;
}

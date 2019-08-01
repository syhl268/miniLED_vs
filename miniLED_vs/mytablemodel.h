#pragma once

#include <QAbstractTableModel>
#include <QColor>

class MyTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	MyTableModel(QObject *parent=nullptr,QColor backColor=QColor(0,0,0), int col=1,int row=1,float *facData=nullptr);
	~MyTableModel();
public:
	// 通过 QAbstractTableModel 继承
	virtual Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const override;

	virtual Q_INVOKABLE int columnCount(const QModelIndex & parent = QModelIndex()) const override;

	virtual Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

	Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex &index) const override;

	bool alterData(const QModelIndex &index, char alterType, float deltaValue);

	void resetData();

	void setFacData(int col,int row,float *facData);//x->col->横坐标->width ; y->row->纵坐标->height

	void setBgColor(QColor);

private:
	float *facData;
	QMap<int, float> backupData;
	int row;
	int col;
	QColor bgColor;
	
};

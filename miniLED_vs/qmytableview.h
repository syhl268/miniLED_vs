#pragma once

#include <QTableView>

class QMyTableView : public QTableView
{
	Q_OBJECT

public:
	QMyTableView(QWidget *parent = Q_NULLPTR);
	~QMyTableView();
protected:
	virtual void wheelEvent(QWheelEvent *event) override;

private:
};

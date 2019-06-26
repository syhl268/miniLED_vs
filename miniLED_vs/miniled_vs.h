#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_miniLED_vs.h"

class miniLED_vs : public QMainWindow
{
	Q_OBJECT

public:
	miniLED_vs(QWidget *parent = Q_NULLPTR);

private:
	Ui::miniLED_vsClass ui;
};

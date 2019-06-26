#pragma once

#include <QObject>

class GlobalVar : public QObject
{
	Q_OBJECT

public:
	GlobalVar(QObject *parent);
	~GlobalVar();
	static QString Ip, WorkPath;
	static int Port;
	static int ScreenWidth, ScreenHeight, BoxWidth, BoxHeight, ModuleWidth, ModuleHeight;
	static int GapUp, GapDown, GapLeft, GapRight;
	static int PartWidth, PartHeight, HoriPartNums, VertPartNums;
	static void init();
};

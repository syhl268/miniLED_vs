#include "miniled_server.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	miniLED_Server w;
	w.setWindowOpacity(1);
	w.setWindowFlags(Qt::FramelessWindowHint);
	w.move(QPoint(0, 0));
	w.setAttribute(Qt::WA_TranslucentBackground,false);
	w.show();
	return a.exec();
}

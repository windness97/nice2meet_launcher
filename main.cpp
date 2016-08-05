#include "roundradiuswindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RoundRadiusWindow w;
	//w.setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
	w.show();
	return a.exec();
}

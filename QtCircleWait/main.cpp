#pragma execution_character_set("utf-8")
#include "QtCircleWait.h"
#include <QtWidgets/QApplication>
#include "CircleWait.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCircleWaitWidget w;
	w.resize(500,150);
	//w.setFont("黑体");
	w.setText("加载中，请耐心等待...");
	w.setColor(QColor(Qt::blue));
	w.show();
	return a.exec();
}

#pragma execution_character_set("utf-8")
#include "QtCircleWait.h"
#include <QtWidgets/QApplication>
#include "CircleWait.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCircleWaitWidget w;
	w.resize(500,150);
	//w.setFont("����");
	w.setText("�����У������ĵȴ�...");
	w.setColor(QColor(Qt::blue));
	w.show();
	return a.exec();
}

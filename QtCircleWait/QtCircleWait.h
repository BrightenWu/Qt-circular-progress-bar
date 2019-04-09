#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtCircleWait.h"

class QtCircleWait : public QWidget
{
	Q_OBJECT

public:
	QtCircleWait(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtCircleWaitClass ui;
};

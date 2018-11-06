#include "stdafx.h"
#include "OverlordEditor.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OverlordEditor w;
	w.show();

	return a.exec();
}

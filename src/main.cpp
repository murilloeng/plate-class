//ext
#include <QApplication>

//plate
#include "Window.h"

int main(int argc, char *argv[])
{
	//application
	QApplication application(argc, argv);
	//window
	Window window;
	//execute
	return application.exec();
}
//ext
#include <QtWidgets/QApplication>

//plate
#include "inc/Window.hpp"

int main(int argc, char *argv[])
{
	//application
	QApplication application(argc, argv);
	//window
	Window window;
	//execute
	return application.exec();
}
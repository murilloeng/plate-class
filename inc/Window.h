#pragma once

//qt
#include <QMainWindow>

class Plate;
namespace Ui
{
	class Window;
}

class Window : public QMainWindow
{
	Q_OBJECT
public:
	//constructors
	Window(void);

	//destructor
	virtual ~Window(void);

	//data
	Plate* m_plate;
	Ui::Window* m_ui;
};
#pragma once

//qt
#include <QtWidgets/QMainWindow>

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

private slots:
	//slots
	virtual void slot_width(void);
	virtual void slot_height(void);
	virtual void slot_thickness(void);

	virtual void slot_elastic(void);
	virtual void slot_poisson(void);
	
	virtual void slot_value(void);
	virtual void slot_size_1(void);
	virtual void slot_size_2(void);
	virtual void slot_position_1(void);
	virtual void slot_position_2(void);
	
	virtual void slot_draw(void);
	virtual void slot_terms(void);
	virtual void slot_mesh_1(void);
	virtual void slot_mesh_2(void);

public:
	//data
	Plate* m_plate;
	Ui::Window* m_ui;
};
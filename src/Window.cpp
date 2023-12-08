//qt
#include <QtWidgets/QMessageBox>

//plate
#include "inc/Plate.hpp"
#include "inc/Window.hpp"

//ui
#include "build/uic/Window.hpp"

//constructors
Window::Window(void) : m_plate(new Plate), m_ui(new Ui::Window)
{
	//setup
	m_ui->setupUi(this);
	setWindowTitle("Plate");
	m_ui->canvas->m_plate = m_plate;
	//edits
	m_ui->edit_width->setText(QString::asprintf("%+.2e", m_plate->m_width));
	m_ui->edit_value->setText(QString::asprintf("%+.2e", m_plate->m_value));
	m_ui->edit_height->setText(QString::asprintf("%+.2e", m_plate->m_height));
	m_ui->edit_size_1->setText(QString::asprintf("%+.2e", m_plate->m_size[0]));
	m_ui->edit_size_2->setText(QString::asprintf("%+.2e", m_plate->m_size[1]));
	m_ui->edit_terms->setText(QString::asprintf("%02d", m_plate->m_draw_terms));
	m_ui->edit_mesh_1->setText(QString::asprintf("%02d", m_plate->m_draw_mesh[0]));
	m_ui->edit_mesh_2->setText(QString::asprintf("%02d", m_plate->m_draw_mesh[1]));
	m_ui->edit_thickness->setText(QString::asprintf("%+.2e", m_plate->m_thickness));
	m_ui->edit_poisson->setText(QString::asprintf("%+.2e", m_plate->m_poisson_ratio));
	m_ui->edit_position_1->setText(QString::asprintf("%+.2e", m_plate->m_position[0]));
	m_ui->edit_position_2->setText(QString::asprintf("%+.2e", m_plate->m_position[1]));
	m_ui->edit_elastic->setText(QString::asprintf("%+.2e", m_plate->m_elastic_modulus));
	//combos
	for(unsigned i = 0; i < unsigned(load_type::last); i++)
	{
		m_ui->combo_type->addItem(Plate::load_name(load_type(i)));
	}
	for(unsigned i = 0; i < unsigned(draw_type::last); i++)
	{
		m_ui->combo_draw->addItem(Plate::draw_name(draw_type(i)));
	}
	//connect
	QObject::connect(m_ui->push_draw, SIGNAL(clicked(bool)), this, SLOT(slot_draw(void)));
	QObject::connect(m_ui->edit_width, SIGNAL(editingFinished(void)), this, SLOT(slot_width(void)));
	QObject::connect(m_ui->edit_value, SIGNAL(editingFinished(void)), this, SLOT(slot_value(void)));
	QObject::connect(m_ui->edit_terms, SIGNAL(editingFinished(void)), this, SLOT(slot_terms(void)));
	QObject::connect(m_ui->edit_height, SIGNAL(editingFinished(void)), this, SLOT(slot_height(void)));
	QObject::connect(m_ui->edit_size_1, SIGNAL(editingFinished(void)), this, SLOT(slot_size_1(void)));
	QObject::connect(m_ui->edit_size_2, SIGNAL(editingFinished(void)), this, SLOT(slot_size_2(void)));
	QObject::connect(m_ui->edit_mesh_1, SIGNAL(editingFinished(void)), this, SLOT(slot_mesh_1(void)));
	QObject::connect(m_ui->edit_mesh_2, SIGNAL(editingFinished(void)), this, SLOT(slot_mesh_2(void)));
	QObject::connect(m_ui->edit_elastic, SIGNAL(editingFinished(void)), this, SLOT(slot_elastic(void)));
	QObject::connect(m_ui->edit_poisson, SIGNAL(editingFinished(void)), this, SLOT(slot_poisson(void)));
	QObject::connect(m_ui->edit_thickness, SIGNAL(editingFinished(void)), this, SLOT(slot_thickness(void)));
	QObject::connect(m_ui->edit_position_1, SIGNAL(editingFinished(void)), this, SLOT(slot_position_1(void)));
	QObject::connect(m_ui->edit_position_2, SIGNAL(editingFinished(void)), this, SLOT(slot_position_2(void)));
	//show
	showMaximized();
}

//destrucor
Window::~Window(void)
{
	delete m_ui;
	delete m_plate;
}

//slots
void Window::slot_width(void)
{
	bool test;
	const double r = m_plate->m_width;
	const double v = m_ui->edit_width->text().toDouble(&test);
	if(test && v > 0)
	{
		m_plate->m_width = v;
		m_ui->edit_width->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_width->setText(QString::asprintf("%+.2e", r));
	}
}
void Window::slot_height(void)
{
	bool test;
	const double r = m_plate->m_height;
	const double v = m_ui->edit_height->text().toDouble(&test);
	if(test && v > 0)
	{
		m_plate->m_height = v;
		m_ui->edit_height->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_height->setText(QString::asprintf("%+.2e", r));
	}
}
void Window::slot_thickness(void)
{
	bool test;
	const double r = m_plate->m_thickness;
	const double v = m_ui->edit_thickness->text().toDouble(&test);
	if(test && v > 0)
	{
		m_plate->m_thickness = v;
		m_ui->edit_thickness->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_thickness->setText(QString::asprintf("%+.2e", r));
	}
}

void Window::slot_elastic(void)
{
	bool test;
	const double r = m_plate->m_elastic_modulus;
	const double v = m_ui->edit_elastic->text().toDouble(&test);
	if(test && v > 0)
	{
		m_plate->m_elastic_modulus = v;
		m_ui->edit_elastic->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_elastic->setText(QString::asprintf("%+.2e", r));
	}
}
void Window::slot_poisson(void)
{
	bool test;
	const double r = m_plate->m_poisson_ratio;
	const double v = m_ui->edit_poisson->text().toDouble(&test);
	if(test && v > 0 && v < 0.5)
	{
		m_plate->m_poisson_ratio = v;
		m_ui->edit_poisson->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_poisson->setText(QString::asprintf("%+.2e", r));
	}
}

void Window::slot_value(void)
{
	bool test;
	const double r = m_plate->m_value;
	const double v = m_ui->edit_value->text().toDouble(&test);
	if(test && v > 0 && v < 0.5)
	{
		m_plate->m_value = v;
		m_ui->edit_value->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_value->setText(QString::asprintf("%+.2e", r));
	}
}
void Window::slot_size_1(void)
{
	bool test;
	const double r = m_plate->m_size[0];
	const double v = m_ui->edit_size_1->text().toDouble(&test);
	if(test && v > 0)
	{
		m_plate->m_size[0] = v;
		m_ui->edit_size_1->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_size_1->setText(QString::asprintf("%+.2e", r));
	}
}
void Window::slot_size_2(void)
{
	bool test;
	const double r = m_plate->m_size[0];
	const double v = m_ui->edit_size_2->text().toDouble(&test);
	if(test && v > 0)
	{
		m_plate->m_size[1] = v;
		m_ui->edit_size_2->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_size_2->setText(QString::asprintf("%+.2e", r));
	}
}
void Window::slot_position_1(void)
{
	bool test;
	const double r = m_plate->m_position[0];
	const double v = m_ui->edit_position_1->text().toDouble(&test);
	if(test && v > 0)
	{
		m_plate->m_position[0] = v;
		m_ui->edit_position_1->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_position_1->setText(QString::asprintf("%+.2e", r));
	}
}
void Window::slot_position_2(void)
{
	bool test;
	const double r = m_plate->m_position[1];
	const double v = m_ui->edit_position_2->text().toDouble(&test);
	if(test && v > 0)
	{
		m_plate->m_position[1] = v;
		m_ui->edit_position_2->setText(QString::asprintf("%+.2e", v));
	}
	else
	{
		m_ui->edit_position_2->setText(QString::asprintf("%+.2e", r));
	}
}

void Window::slot_draw(void)
{
	//check
	const double w = m_plate->m_width;
	const double h = m_plate->m_height;
	const double s1 = m_plate->m_size[0];
	const double s2 = m_plate->m_size[1];
	const double p1 = m_plate->m_position[0];
	const double p2 = m_plate->m_position[1];
	if(p1 - s1 / 2 < 0 || p1 + s1 / 2 > w || p2 - s2 / 2 < 0 || p2 + s2 / 2 > h)
	{
		QMessageBox::warning(nullptr, "Warning", "Invalid load parameters!");
		return;
	}
	m_plate->setup();
	m_ui->canvas->setup();
	m_ui->canvas->update();
}
void Window::slot_terms(void)
{
	bool test;
	const unsigned r = m_plate->m_draw_terms;
	const unsigned v = m_ui->edit_terms->text().toUInt(&test);
	if(test)
	{
		m_plate->m_draw_terms = v;
		m_ui->edit_terms->setText(QString::asprintf("%02d", v));
	}
	else
	{
		m_ui->edit_terms->setText(QString::asprintf("%02d", r));
	}
}
void Window::slot_mesh_1(void)
{
	bool test;
	const unsigned r = m_plate->m_draw_mesh[0];
	const unsigned v = m_ui->edit_mesh_1->text().toUInt(&test);
	if(test)
	{
		m_plate->m_draw_mesh[0] = v;
		m_ui->edit_mesh_1->setText(QString::asprintf("%02d", v));
	}
	else
	{
		m_ui->edit_mesh_1->setText(QString::asprintf("%02d", r));
	}
}
void Window::slot_mesh_2(void)
{
	bool test;
	const unsigned r = m_plate->m_draw_mesh[1];
	const unsigned v = m_ui->edit_mesh_2->text().toUInt(&test);
	if(test)
	{
		m_plate->m_draw_mesh[1] = v;
		m_ui->edit_mesh_2->setText(QString::asprintf("%02d", v));
	}
	else
	{
		m_ui->edit_mesh_2->setText(QString::asprintf("%02d", r));
	}
}
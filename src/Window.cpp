//plate
#include "Plate.h"
#include "Window.h"

//ui
#include "uic/Window.h"

//constructors
Window::Window(void) : m_plate(new Plate), m_ui(new Ui::Window)
{
	//setup
	m_ui->setupUi(this);
	setWindowTitle("Plate");
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
	//show
	showMaximized();
}

//destrucor
Window::~Window(void)
{
	delete m_ui;
	delete m_plate;
}
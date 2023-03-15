#include "Plate.h"

//constructor
Plate::Plate(void) : 
	m_width(1e0), m_height(1e0), m_thickness(1e-2), 
	m_value(0), m_size{5e-1, 5e-1}, m_position{0, 0}, m_load_type(load_type::patch), 
	m_elastic_modulus(2e11), m_poisson_ratio(3e-1),
	m_draw_type(draw_type::U3), m_draw_terms(10), m_draw_mesh{10, 10}
{
	return;
}

//destructor
Plate::~Plate(void)
{
	return;
}

//name
const char* Plate::load_name(load_type type)
{
	switch(type)
	{
	case load_type::patch:
		return "Patch";
	case load_type::point:
		return "Point";
	case load_type::line_H:
		return "Line H";
	case load_type::line_V:
		return "Line V";
	default:
		return "Error";
	}
}
const char* Plate::draw_name(draw_type type)
{
	switch(type)
	{
	case draw_type::U3:
		return "U3";
	case draw_type::R1:
		return "R1";
	case draw_type::R2:
		return "R2";
	case draw_type::M11:
		return "M11";
	case draw_type::M12:
		return "M12";
	case draw_type::M22:
		return "M22";
	default:
		return "Error";
	}
}
const char* Plate::load_name(void) const
{
	return load_name(m_load_type);
}
const char* Plate::draw_name(void) const
{
	return draw_name(m_draw_type);
}
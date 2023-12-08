//std
#include <cmath>

//project
#include "inc/Plate.hpp"

//constructor
Plate::Plate(void) : 
	m_width(1e0), m_height(1e0), m_thickness(1e-2), 
	m_value(0), m_size{5e-1, 5e-1}, m_position{5e-1, 5e-1}, m_load_type(load_type::point), 
	m_elastic_modulus(2e11), m_poisson_ratio(3e-1),
	m_draw_type(draw_type::U3), m_draw_terms(10), m_draw_mesh{100, 100},
	m_q(nullptr), m_u3(nullptr), m_t1(nullptr), m_t2(nullptr)
{
	return;
}

//destructor
Plate::~Plate(void)
{
	delete[] m_q;
	delete[] m_u3;
	delete[] m_t1;
	delete[] m_t2;
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
	case draw_type::model:
		return "Model";
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

//solution
void Plate::setup(void)
{
	//geometry
	const double q = m_value;
	const double w = m_width;
	const double h = m_height;
	//load
	const double s1 = m_size[0];
	const double s2 = m_size[1];
	const double x1 = m_position[0];
	const double x2 = m_position[1];
	//stiffness
	const double t = m_thickness;
	const double v = m_poisson_ratio;
	const double E = m_elastic_modulus;
	const double D = E * t * t * t / 12 / (1 - v * v);
	//series
	const unsigned nt = m_draw_terms;
	//memory
	delete[] m_q;
	delete[] m_u3;
	delete[] m_t1;
	delete[] m_t2;
	m_q = new double[nt * nt];
	m_u3 = new double[nt * nt];
	m_t1 = new double[nt * nt];
	m_t2 = new double[nt * nt];
	//terms
	for(unsigned i = 0; i < nt; i++)
	{
		for(unsigned j = 0; j < nt; j++)
		{
			if(m_load_type == load_type::point)
			{
				m_q[nt * i + j] = 4 * q / w / h * sin((i + 1) * M_PI * x1 / w) * sin((j + 1) * M_PI * x2 / h);
				m_u3[nt * i + j] = m_q[nt * i + j] / D / pow(pow((i + 1) * M_PI / w, 2) + pow((j + 1) * M_PI / h, 2), 2);
				m_t1[nt * i + j] = +m_u3[nt * i + j] * (j + 1) * M_PI / h;
				m_t2[nt * i + j] = -m_u3[nt * i + j] * (i + 1) * M_PI / w;
			}
		}
	}
}
double Plate::solution(unsigned index, const double* position) const
{
	double value = 0;
	const double w = m_width;
	const double h = m_height;
	const double* x = position;
	const unsigned nt = m_draw_terms;
	for(unsigned i = 0; i < nt; i++)
	{
		for(unsigned j = 0; j < nt; j++)
		{
			if(index == 0)
			{
				value += m_u3[nt * i + j] * sin((i + 1) * M_PI * x[0] / w) * sin((j + 1) * M_PI * x[1] / h);
			}
		}
	}
	return value;
}
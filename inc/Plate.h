#pragma once

enum class load_type : unsigned
{
	patch,
	point,
	line_H,
	line_V,
	last
};

enum class draw_type : unsigned
{
	U3,
	R1,
	R2,
	M11,
	M12,
	M22,
	last
};

class Plate
{
public:
	//constructors
	Plate(void);

	//destructor
	virtual ~Plate(void);

	//name
	static const char* load_name(load_type);
	static const char* draw_name(draw_type);
	virtual const char* load_name(void) const;
	virtual const char* draw_name(void) const;

	//data
	double m_width;
	double m_height;
	double m_thickness;
	
	double m_value;
	double m_size[2];
	double m_position[2];
	load_type m_load_type;
	
	double m_poisson_ratio;
	double m_elastic_modulus;
	
	draw_type m_draw_type;
	unsigned m_draw_terms;
	unsigned m_draw_mesh[2];
};
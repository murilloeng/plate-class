#pragma once

class Palette
{
public:
	//constructors
	Palette(void);

	//destructor
	virtual ~Palette(void);

	//color
	virtual void color(double*, double) const;

	//data
	double m_min;
	double m_max;
	static const double m_colors[27];
};
//project
#include "Palette.h"

//constructor
Palette::Palette(void) : m_min(0), m_max(1)
{
	return;
}

//destructor
Palette::~Palette(void)
{
	return;
}

//color
void Palette::color(double* color, double value) const
{
	if(m_min == m_max)
	{
		value = 0.5;
	}
	else
	{
		value = (value - m_min) / (m_max - m_min);
	}
	const unsigned n = sizeof(m_colors) / sizeof(double) / 3;
	const unsigned a = unsigned(n * value);
	const double s = n * value - a;
	color[0] = (1 - s) * m_colors[3 * a + 0] + s * m_colors[3 * a + 3];
	color[1] = (1 - s) * m_colors[3 * a + 1] + s * m_colors[3 * a + 4];
	color[2] = (1 - s) * m_colors[3 * a + 2] + s * m_colors[3 * a + 5];
}

//static data
const double Palette::m_colors[27] = {
	0.00000, 0.00000, 0.50000,
	0.00000, 0.00000, 1.00000,
	0.00000, 0.50000, 1.00000,
	0.00000, 1.00000, 1.00000,
	0.50000, 1.00000, 0.50000,
	1.00000, 1.00000, 0.00000,
	1.00000, 0.50000, 0.00000,
	1.00000, 0.00000, 0.00000,
	0.50000, 0.00000, 0.00000
};
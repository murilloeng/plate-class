//qt
#include <QOpenGLFunctions>

//project
#include "Plate.h"
#include "Canvas.h"
#include "Palette.h"

//constructor
Canvas::Canvas(QWidget* parent) : QOpenGLWidget(parent), 
	m_plate(nullptr), m_palette(new Palette), m_vbo(QOpenGLBuffer::VertexBuffer), m_ibo(QOpenGLBuffer::IndexBuffer)
{
	return;
}

//destructor
Canvas::~Canvas(void)
{
	delete m_palette;
}

//draw
void Canvas::setup(void)
{
	//data
	const double w = m_plate->m_width;
	const double h = m_plate->m_height;
	const unsigned n1 = m_plate->m_draw_mesh[0];
	const unsigned n2 = m_plate->m_draw_mesh[1];
	//uniform
	glUniform1f(m_program.uniformLocation("size"), fmax(w, h) / 2);
	glUniform2f(m_program.uniformLocation("center"), w / 2, h / 2);
	//draw
	const unsigned nt = 2 * n1 * n2;
	const unsigned nv = (n1 + 1) * (n2 + 1);
	//vbo
	float* x = new float[6 * nv];
	for(unsigned i = 0; i <= n2; i++)
	{
		for(unsigned j = 0; j <= n1; j++)
		{
			x[6 * ((n1 + 1) * i + j) + 2] = 0;
			x[6 * ((n1 + 1) * i + j) + 0] = j * w / n1;
			x[6 * ((n1 + 1) * i + j) + 1] = i * h / n2;

			double color[3];
			const double x1 = double(j) / n1;
			const double x2 = double(i) / n2;
			m_palette->color(color, 16 * x1 * (1 - x1) * x2 * (1 - x2));

			x[6 * ((n1 + 1) * i + j) + 3] = color[0];
			x[6 * ((n1 + 1) * i + j) + 4] = color[1];
			x[6 * ((n1 + 1) * i + j) + 5] = color[2];
		}
	}
	m_vbo.bind();
	m_vbo.allocate(x, 6 * nv * sizeof(float));
	//ibo
	unsigned* e = new unsigned[3 * nt];
	for(unsigned i = 0; i < n2; i++)
	{
		for(unsigned j = 0; j < n1; j++)
		{
			e[6 * (n1 * i + j) + 0] = (n1 + 1) * (i + 0) + j + 0;
			e[6 * (n1 * i + j) + 1] = (n1 + 1) * (i + 0) + j + 1;
			e[6 * (n1 * i + j) + 2] = (n1 + 1) * (i + 1) + j + 1;
			e[6 * (n1 * i + j) + 3] = (n1 + 1) * (i + 0) + j + 0;
			e[6 * (n1 * i + j) + 4] = (n1 + 1) * (i + 1) + j + 1;
			e[6 * (n1 * i + j) + 5] = (n1 + 1) * (i + 1) + j + 0;
		}
	}
	m_ibo.bind();
	m_ibo.allocate(e, 3 * nt * sizeof(unsigned));
	//cleanup
	delete[] x;
	delete[] e;
}
void Canvas::paintGL(void)
{
	//clear
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw
	const unsigned n1 = m_plate->m_draw_mesh[0];
	const unsigned n2 = m_plate->m_draw_mesh[1];
	glDrawElements(GL_TRIANGLES, 6 * n1 * n2, GL_UNSIGNED_INT, 0);
}
void Canvas::resizeGL(int w, int h)
{
	glUniform2i(m_program.uniformLocation("screen"), w, h);
}
void Canvas::initializeGL(void)
{
	//glew
	initializeOpenGLFunctions();
	//program
	if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/vs.glsl"))
	{
		printf("%s\n", m_program.log().toUtf8().data());
		exit(EXIT_FAILURE);
	}
	if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/fs.glsl"))
	{
		printf("%s\n", m_program.log().toUtf8().data());
		exit(EXIT_FAILURE);
	}
	if(!m_program.link())
	{
		printf("%s\n", m_program.log().toUtf8().data());
		exit(EXIT_FAILURE);
	}
	if(!m_program.bind())
	{
		printf("%s\n", m_program.log().toUtf8().data());
		exit(EXIT_FAILURE);
	}
	//buffers
	if(!m_vbo.create())
	{
		exit(EXIT_FAILURE);
	}
	if(!m_ibo.create())
	{
		exit(EXIT_FAILURE);
	}
	m_plate->setup();
	setup();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}
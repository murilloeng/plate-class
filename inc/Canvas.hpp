#pragma once

//qt
#include <QtGui/QOpenGLFunctions>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGLWidgets/QOpenGLWidget>

class Plate;
class Palette;

class Canvas : public QOpenGLWidget, public QOpenGLFunctions
{
	Q_OBJECT

public:
	//constructors
	Canvas(QWidget*);

	//destructor
	virtual ~Canvas(void);

	//draw
	virtual void setup(void);
	virtual void paintGL(void) override;
	virtual void resizeGL(int, int) override;
	virtual void initializeGL(void) override;

	//data
	Plate* m_plate;
	Palette* m_palette;
	QOpenGLBuffer m_vbo;
	QOpenGLBuffer m_ibo;
	QOpenGLShaderProgram m_program;
};
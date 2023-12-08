//maker
#include "../Maker/inc/Maker.hpp"

void setup_dlls(Maker& maker)
{
	maker.m_path_dll.clear();
	maker.m_path_dll.push_back(maker.m_edll + "glew32.dll");
	maker.m_path_dll.push_back(maker.m_edll + "freetype.dll");
	maker.m_path_dll.push_back(maker.m_edll + "gmsh-4.9.dll");
}
void setup_libs(Maker& maker)
{
	maker.m_libs.clear();
	maker.m_libs += "opengl32.lib ";
	maker.m_libs += maker.m_elib + "glew32.lib ";
	maker.m_libs += maker.m_elib + "freetype.lib ";
	maker.m_libs += maker.m_qt_dir + "lib/Qt6Gui.lib ";
	maker.m_libs += maker.m_qt_dir + "lib/Qt6Core.lib ";
	maker.m_libs += maker.m_qt_dir + "lib/Qt6OpenGL.lib ";
	maker.m_libs += maker.m_qt_dir + "lib/Qt6Widgets.lib ";
	maker.m_libs += maker.m_qt_dir + "lib/Qt6OpenGLWidgets.lib ";
}

int main(int argc, char** argv)
{
	//setup
	Maker maker;
	maker.m_gui = true;
	maker.m_out = "plate";
	maker.setup(argc, argv);
	maker.m_elib = "../external/cpp/lib/x64/";
	maker.m_edll = "../external/cpp/dll/x64/";
	maker.m_qt_dir = "C:/Qt/6.4.3/msvc2019_64/";
	maker.m_incs = "/I . /I " + maker.m_qt_dir + "include ";
	//build
	if(!maker.m_clean)
	{
		setup_libs(maker);
		setup_dlls(maker);
		maker.build_uic();
		maker.build_inc();
		maker.build_src();
		maker.build_moc();
		maker.build_dll();
		maker.build_exe();
		maker.build_run();
		maker.build_debug();
	}
	else
	{
		maker.build_clean();
	}
	//return
	return EXIT_SUCCESS;
}
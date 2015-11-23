//
// main.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 23:31:52 2015 chapui_s
// Last update Tue Nov 10 23:31:52 2015 chapui_s
//

# include "IGraphicEngine.hh"
# include "GraphicEngine.hh"
#include "PackageStorage.hh"
#include "Packager.hh"

#ifdef _WIN32
# include "WSA.hh"
#endif // !_WIN32

int		main(int argc, char **argv)
{
#ifdef _WIN32
	if (WSA::init()) {
		return (-1);
	}
#endif // !_WIN32

#ifdef _WIN32
	WSA::clean();
#endif // !_WIN32

	
	
	
	IGraphicEngine* engine = new GraphicEngine;
	Packager *packager = new Packager();

	engine->createWindow(800, 600, "R-Type");
	engine->launch();
	delete engine;
	delete packager;
	return (0);
}

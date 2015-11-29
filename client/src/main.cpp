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
#include "NetworkClient.hh"
#include "DisplayUpdater.hh"

#ifdef _WIN32
# include "WSA.hh"
#endif // !_WIN32

int		main(int argc UNUSED, char **argv UNUSED) // Enlevez les UNUSED quand vous les utiliserez
{
#ifdef _WIN32
	if (WSA::init()) {
		return (-1);
	}
#endif // !_WIN32

	try {
		Packager *packager = new Packager();
		/*IGraphicEngine* engine = new GraphicEngine(packager);*/
		NetworkClient* network = new NetworkClient("127.0.0.1", 4242);
		DisplayUpdater updater(packager);

		PaquetFirst paquet;
		paquet.setLevel(5);
		paquet.setName("Alex");
		paquet.setVersion(0);
		network->handleFirst(paquet);

		/*engine->createWindow(800, 600, "R-Type");
		engine->launch();*/
		//delete engine;
		delete packager;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
#ifdef _WIN32
		system("pause");
#endif
	}

#ifdef _WIN32
	WSA::clean();
#endif // !_WIN32

	return (0);
}

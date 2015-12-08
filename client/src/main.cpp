//
// main.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 23:31:52 2015 chapui_s
// Last update Tue Nov 10 23:31:52 2015 chapui_s
//

#include "IGraphicEngine.hh"
#include "GraphicEngine.hh"
#include "PackageStorage.hh"
#include "Packager.hh"
#include "NetworkClient.hh"
#include "DisplayUpdater.hh"
#include "PackageSorter.hh"
#include "Tools.hh"
#include "ListPlayers.hh"

#ifdef _WIN32
# include "WSA.hh"
#endif // !_WIN32

#include "SystemAudio.hh"

bool isNumber(const std::string& s)
{
	return (Tools::findIn(s, [](char c) { return !(c >= '0' && c <= '9'); }) == false);
}

int		main(int argc, char **argv)
{

	uint16_t port(4242);
	//alex
	//std::string addr("82.229.96.158");
	//localhost
	std::string addr("84.102.232.137");
	//seb
	//std::string addr("84.102.232.137");

	if (argc == 2 || (argc > 2 && !isNumber(argv[2]))) {
		std::cerr << "usage: " << argv[0] << " <server> <port>" << std::endl;
		return (0);
	}

	if (argc > 2) {
		addr = argv[1];
		try {
			port = std::stoi(argv[2]);
		}
		catch (std::out_of_range &) {
			std::cerr << "Wrong port value. Use port " << port << std::endl;
		}
	}

#ifdef _WIN32
	if (WSA::init()) {
		return (-1);
	}
#endif // !_WIN32

	ISystemAudio &audio = SystemAudio::getInstance();

	try {
		audio.loadMusic("test.ogg", 1);
		audio.loadMusic("crazyfrog.ogg", 2);
		audio.loadMusic("eiffel65.ogg", 3);
		audio.loadMusic("booba.ogg", 4);
		audio.loadMusic("tupac.ogg", 5);
		audio.loadSound("simple_shot.wav", ISystemAudio::SIMPLE_SHOT);
	}
	catch (ErrorLoadingFile &) {
		DEBUG_MSG("Can't load music");
	}
	audio.playMusicRandom();

	try {
		Packager *packager = new Packager();
		NetworkClient* network = new NetworkClient(addr, port);
		PackageSorter sorter;
		DisplayUpdater updater(packager, network);

		delete packager;
		delete network;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
#ifdef _WIN32
		system("pause");
#endif
	}

	delete &audio;

#ifdef _WIN32
	WSA::clean();
#endif // !_WIN32

	return (0);
}

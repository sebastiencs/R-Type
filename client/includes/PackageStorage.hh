#ifndef PACKAGESTORAGE_HH
#define PACKAGESTORAGE_HH

#include <iostream>
#include <list>
#include "Paquet.hh"

class PackageStorage {
private:

	std::list<Paquet *> received;
	std::list<Paquet *> toSend;
	std::list<Paquet *> players;
	std::list<Paquet *> enemies;
	std::list<Paquet *> obstacles;
	std::list<Paquet *> shots;

public:

	
};

#endif
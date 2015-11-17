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

	PackageStorage();
	virtual ~PackageStorage();
	
	const Paquet *getReceivedPackage() const;
	const Paquet *getPlayersPackage() const;
	const Paquet *getEnemiesPackage() const;
	const Paquet *getObstaclesPackage() const;
	const Paquet *getShotsPackage() const;
	
	void storeReceivedPackage(Paquet *package);
	void storePlayersPackage(Paquet *package);
	void storeEnemiesPackage(Paquet *package);
	void storeObstaclesPackage(Paquet *package);
	void storeShotsPackage(Paquet *package);

};

#endif
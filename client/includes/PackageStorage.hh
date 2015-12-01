#ifndef PACKAGESTORAGE_HH
#define PACKAGESTORAGE_HH

#include <iostream>
#include <list>
#include "Paquets.hh"
#include "Paquet.hh"
#include "Semaphore.hh"

class PackageStorage {
private:

	std::list<Paquet *> received;
	std::list<Paquet *> toSend;
	std::list<Paquet *> players;
	std::list<Paquet *> enemies;
	std::list<Paquet *> obstacles;
	std::list<Paquet *> shots;
	std::list<Paquet *> gameList;
	std::list<Paquet *> playerList;
	std::list<Paquet *> answers;
	std::list<Paquet * > launch;

  std::unique_ptr<ISemaphore>	_sem;

	PackageStorage();

public:

	static PackageStorage& getInstance();

	virtual ~PackageStorage();

	const Paquet *getReceivedPackage() const;
	const PaquetPlayerCoord *getPlayersPackage() const;
	const PaquetPlayerCoord *getEnemiesPackage() const;
	const PaquetObstacle *getObstaclesPackage() const;
	const PaquetPlayerShot *getShotsPackage() const;
	const Paquet *getToSendPackage() const;
	const PaquetListParties *getGameListPackage() const;
	const PaquetListPlayers *getPlayerListPackage() const;
	const PaquetResponse *getAnswersPackage() const;
	const PaquetLaunch *getLaunchPackage() const;

	void storeReceivedPackage(Paquet *package);
	void storePlayersPackage(Paquet *package);
	void storeEnemiesPackage(Paquet *package);
	void storeObstaclesPackage(Paquet *package);
	void storeShotsPackage(Paquet *package);
	void storeToSendPackage(Paquet *package);
	void storeGameListPackage(Paquet *package);
	void storePlayerListPackage(Paquet *package);
	void storeAnswersPackage(Paquet *package);
	void storeLaunchPackage(Paquet *package);

	void deleteReceivedPackage();
	void deletePlayersPackage();
	void deleteEnemiesPackage();
	void deleteObstaclesPackage();
	void deleteShotsPackage();
	void deleteToSendPackage();
	void deleteGameListPackage();
	void deletePlayerListPackage();
	void deleteAnswersPackage();
	void deleteLaunchPackage();

	bool isThereReceivedPackage();
	void waitForPackage();
	/*bool deletePlayersPackage();
	bool deleteEnemiesPackage();
	bool deleteObstaclesPackage();
	bool deleteShotsPackage();
	bool deleteToSendPackage();
	bool deleteGameListPackage();
	bool deletePlayerListPackage();
	bool deleteAnswersPackage();*/
};

#endif

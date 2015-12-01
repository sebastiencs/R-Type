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
	std::list<PaquetPlayerCoord *> players;
	std::list<PaquetPlayerCoord *> enemies;
	std::list<PaquetObstacle *> obstacles;
	std::list<PaquetPlayerShot *> shots;
	std::list<PaquetListParties *> gameList;
	std::list<PaquetListPlayers *> playerList;
	std::list<PaquetResponse *> answers;
	std::list<PaquetLaunch * > launch;

  std::unique_ptr<ISemaphore>	_semOut;
  std::unique_ptr<ISemaphore>	_semIn;

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
	void storePlayersPackage(PaquetPlayerCoord *package);
	void storeEnemiesPackage(PaquetPlayerCoord *package);
	void storeObstaclesPackage(PaquetObstacle *package);
	void storeShotsPackage(PaquetPlayerShot *package);
	void storeToSendPackage(Paquet *package);
	void storeGameListPackage(PaquetListParties *package);
	void storePlayerListPackage(PaquetListPlayers *package);
	void storeAnswersPackage(PaquetResponse *package);
	void storeLaunchPackage(PaquetLaunch *package);

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

	void waitForReceivedPackage();
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

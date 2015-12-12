#ifndef PACKAGESTORAGE_HH
#define PACKAGESTORAGE_HH

#include <iostream>
#include <deque>
#include "Paquets.hh"
#include "Paquet.hh"
#include "Semaphore.hh"

class PackageStorage {
private:

	std::deque<Paquet *> received;
	std::deque<Paquet *> toSendUDP;
	std::deque<Paquet *> toSendTCP;
	std::deque<PaquetPlayerCoord *> players;
	std::deque<PaquetPlayerCoord *> enemies;
	std::deque<PaquetObstacle *> obstacles;
	std::deque<PaquetPlayerShot *> shots;
	std::deque<PaquetReady *> ready;
	std::deque<PaquetListParties *> gameList;
	std::deque<PaquetListPlayers *> playerList;
	std::deque<PaquetResponse *> answers;
	std::deque<PaquetLaunch *> launch;
	std::deque<PaquetLeave *> leave;
	std::deque<PaquetEnemy *> enemy;
	std::deque<PaquetBonusMalus *> bonusmalus;

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
	const PaquetReady *getReadyPackage() const;
	const Paquet *getToSendUDPPackage() const;
	const Paquet *getToSendTCPPackage() const;
	const PaquetListParties *getGameListPackage() const;
	const PaquetListPlayers *getPlayerListPackage() const;
	const PaquetResponse *getAnswersPackage() const;
	const PaquetLaunch *getLaunchPackage() const;
	const PaquetLeave *getLeavePackage() const;
	const PaquetEnemy *getEnemyPackage() const;
	const PaquetBonusMalus *getBonusMalusPackage() const;

	void storeReceivedPackage(Paquet *package);
	void storePlayersPackage(PaquetPlayerCoord *package);
	void storeEnemiesPackage(PaquetPlayerCoord *package);
	void storeObstaclesPackage(PaquetObstacle *package);
	void storeShotsPackage(PaquetPlayerShot *package);
	void storeReadyPackage(PaquetReady *package);
	void storeToSendUDPPackage(Paquet *package);
	void storeToSendTCPPackage(Paquet *package);
	void storeGameListPackage(PaquetListParties *package);
	void storePlayerListPackage(PaquetListPlayers *package);
	void storeAnswersPackage(PaquetResponse *package);
	void storeLaunchPackage(PaquetLaunch *package);
	void storeLeavePackage(PaquetLeave *package);
	void storeEnemyPackage(PaquetEnemy *package);
	void storeBonusMalusPackage(PaquetBonusMalus *package);

	void deleteReceivedPackage();
	void deletePlayersPackage();
	void deleteEnemiesPackage();
	void deleteObstaclesPackage();
	void deleteShotsPackage();
	void deleteReadyPackage();
	void deleteToSendUDPPackage();
	void deleteToSendTCPPackage();
	void deleteGameListPackage();
	void deletePlayerListPackage();
	void deleteAnswersPackage();
	void deleteLaunchPackage();
	void deleteLeavePackage();
	void deleteEnemyPackage();
	void deleteBonusMalusPackage();

	void waitForReceivedPackage();
	bool isThereReceivedPackage();
	void waitForPackage();
};

#endif

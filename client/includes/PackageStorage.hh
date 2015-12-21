#ifndef PACKAGESTORAGE_HH
#define PACKAGESTORAGE_HH

#include <iostream>
#include <deque>
#include "Paquets.hh"
#include "Paquet.hh"
#include "Semaphore.hh"
#include "DequeSecure.hh"

typedef std::shared_ptr<Paquet> Paquet_SharedPtr;
typedef std::shared_ptr<PaquetEnemy> PaquetEnemy_SharedPtr;

class PackageStorage {
private:

	DequeSecure<Paquet_SharedPtr> received;
	DequeSecure<Paquet *> toSendUDP;
	DequeSecure<Paquet *> toSendTCP;
	DequeSecure<PaquetPlayerCoord *> players;
	//DequeSecure<PaquetPlayerCoord *> enemies;
	DequeSecure<PaquetObstacle *> obstacles;
	DequeSecure<PaquetPlayerShot *> shots;
	DequeSecure<PaquetReady *> ready;
	DequeSecure<PaquetListParties *> gameList;
	DequeSecure<PaquetListPlayers *> playerList;
	DequeSecure<PaquetResponse *> answers;
	DequeSecure<PaquetLaunch *> launch;
	DequeSecure<PaquetLeave *> leave;
	DequeSecure<PaquetEnemy_SharedPtr> enemy;
	DequeSecure<PaquetBonusMalus *> bonusmalus;
	DequeSecure<PaquetLife *> life;
	DequeSecure<PaquetDeath *> death;

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
	const PaquetLife *getLifePackage() const;
	const PaquetDeath *getDeathPackage() const;

	void storeReceivedPackage(Paquet_SharedPtr package);
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
	void storeEnemyPackage(PaquetEnemy_SharedPtr package);
	void storeBonusMalusPackage(PaquetBonusMalus *package);
	void storeLifePackage(PaquetLife *package);
	void storeDeathPackage(PaquetDeath *package);

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
	void deleteLifePackage();
	void deleteDeathPackage();

	void waitForReceivedPackage();
	bool isThereReceivedPackage();
	void waitForPackage();
};

#endif

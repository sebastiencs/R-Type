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
	DequeSecure<Paquet_SharedPtr> toSendUDP;
	DequeSecure<Paquet_SharedPtr> toSendTCP;
	DequeSecure<PaquetPlayerCoord_SharedPtr> players;
	DequeSecure<PaquetObstacle_SharedPtr> obstacles;
	DequeSecure<PaquetPlayerShot_SharedPtr> shots;
	DequeSecure<PaquetReady_SharedPtr> ready;
	DequeSecure<PaquetListParties_SharedPtr> gameList;
	DequeSecure<PaquetListPlayers_SharedPtr> playerList;
	DequeSecure<PaquetResponse_SharedPtr> answers;
	DequeSecure<PaquetLaunch_SharedPtr> launch;
	DequeSecure<PaquetLeave_SharedPtr> leave;
	DequeSecure<PaquetEnemy_SharedPtr> enemy;
	DequeSecure<PaquetBonusMalus_SharedPtr> bonusmalus;
	DequeSecure<PaquetLife_SharedPtr> life;
	DequeSecure<PaquetDeath_SharedPtr> death;
	DequeSecure<PaquetAttrBonus_SharedPtr> attrbonus;

	std::unique_ptr<ISemaphore>	_semOut;
	std::unique_ptr<ISemaphore>	_semIn;

  	PackageStorage();

public:

	static PackageStorage& getInstance();

	virtual ~PackageStorage();

	const Paquet_SharedPtr getReceivedPackage() const;
	const PaquetPlayerCoord_SharedPtr getPlayersPackage() const;
	const PaquetPlayerCoord_SharedPtr getEnemiesPackage() const;
	const PaquetObstacle_SharedPtr getObstaclesPackage() const;
	const PaquetPlayerShot_SharedPtr getShotsPackage() const;
	const PaquetReady_SharedPtr getReadyPackage() const;
	const Paquet_SharedPtr getToSendUDPPackage() const;
	const Paquet_SharedPtr getToSendTCPPackage() const;
	const PaquetListParties_SharedPtr getGameListPackage() const;
	const PaquetListPlayers_SharedPtr getPlayerListPackage() const;
	const PaquetResponse_SharedPtr getAnswersPackage() const;
	const PaquetLaunch_SharedPtr getLaunchPackage() const;
	const PaquetLeave_SharedPtr getLeavePackage() const;
	const PaquetEnemy_SharedPtr getEnemyPackage() const;
	const PaquetBonusMalus_SharedPtr getBonusMalusPackage() const;
	const PaquetLife_SharedPtr getLifePackage() const;
	const PaquetDeath_SharedPtr getDeathPackage() const;
	const PaquetAttrBonus_SharedPtr getAttrBonusPackage() const;

	void storeReceivedPackage(Paquet_SharedPtr package);
	void storePlayersPackage(PaquetPlayerCoord_SharedPtr package);
	void storeEnemiesPackage(PaquetPlayerCoord_SharedPtr package);
	void storeObstaclesPackage(PaquetObstacle_SharedPtr package);
	void storeShotsPackage(PaquetPlayerShot_SharedPtr package);
	void storeReadyPackage(PaquetReady_SharedPtr package);
	void storeToSendUDPPackage(Paquet_SharedPtr package);
	void storeToSendTCPPackage(Paquet_SharedPtr package);
	void storeGameListPackage(PaquetListParties_SharedPtr package);
	void storePlayerListPackage(PaquetListPlayers_SharedPtr package);
	void storeAnswersPackage(PaquetResponse_SharedPtr package);
	void storeLaunchPackage(PaquetLaunch_SharedPtr package);
	void storeLeavePackage(PaquetLeave_SharedPtr package);
	void storeEnemyPackage(PaquetEnemy_SharedPtr package);
	void storeBonusMalusPackage(PaquetBonusMalus_SharedPtr package);
	void storeLifePackage(PaquetLife_SharedPtr package);
	void storeDeathPackage(PaquetDeath_SharedPtr package);
	void storeAttrBonusPackage(PaquetAttrBonus_SharedPtr package);

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
	void deleteAttrBonusPackage();

	void waitForReceivedPackage();
	bool isThereReceivedPackage();
	bool waitForPackage();
};

typedef std::shared_ptr<PackageStorage> PackageStorage_SharedPtr;

#endif

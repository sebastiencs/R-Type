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
	std::list<Paquet *> gameList;
	std::list<Paquet *> playerList;
	std::list<Paquet *> answers;
	std::list<Paquet * > launch;

public:

	static PackageStorage& getInstance();

	PackageStorage();
	virtual ~PackageStorage();
	
	const Paquet *getReceivedPackage() const;
	const Paquet *getPlayersPackage() const;
	const Paquet *getEnemiesPackage() const;
	const Paquet *getObstaclesPackage() const;
	const Paquet *getShotsPackage() const;
	const Paquet *getToSendPackage() const;
	const Paquet *getGameListPackage() const;
	const Paquet *getPlayerListPackage() const;
	const Paquet *getAnswersPackage() const;
	const Paquet *getLaunchPackage() const;

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
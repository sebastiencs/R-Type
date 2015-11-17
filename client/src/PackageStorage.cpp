#include "..\includes\PackageStorage.hh"

PackageStorage::PackageStorage()
{
}

PackageStorage::~PackageStorage()
{
}

const Paquet *PackageStorage::getReceivedPackage() const {
	return received.front();
}

const Paquet *PackageStorage::getPlayersPackage() const {
	return players.front();
}

const Paquet *PackageStorage::getEnemiesPackage() const {
	return enemies.front();
}

const Paquet *PackageStorage::getObstaclesPackage() const {
	return obstacles.front();
}

const Paquet * PackageStorage::getShotsPackage() const
{
	return shots.front();
}

const Paquet * PackageStorage::getToSendPackage() const
{
	return toSend.front();
}

void PackageStorage::storeReceivedPackage(Paquet * package)
{
	received.push_back(package);
}

void PackageStorage::storePlayersPackage(Paquet * package)
{
	players.push_back(package);
}

void PackageStorage::storeEnemiesPackage(Paquet * package)
{
	enemies.push_back(package);
}

void PackageStorage::storeObstaclesPackage(Paquet * package)
{
	obstacles.push_back(package);
}

void PackageStorage::storeShotsPackage(Paquet * package)
{
	shots.push_back(package);
}

void PackageStorage::storeToSendPackage(Paquet * package)
{
	toSend.push_back(package);
}

void PackageStorage::deleteReceivedPackage()
{
	received.erase(received.begin());
}

void PackageStorage::deletePlayersPackage()
{
	players.erase(received.begin());
}

void PackageStorage::deleteEnemiesPackage()
{
	enemies.erase(received.begin());
}

void PackageStorage::deleteObstaclesPackage()
{
	obstacles.erase(received.begin());
}

void PackageStorage::deleteShotsPackage()
{
	shots.erase(received.begin());
}

void PackageStorage::deleteToSendPackage()
{
	toSend.erase(received.begin());
}



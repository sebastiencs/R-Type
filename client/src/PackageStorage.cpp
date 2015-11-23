#include "PackageStorage.hh"

PackageStorage & PackageStorage::getInstance()
{
	static PackageStorage *instance;
	if (instance == nullptr) {
		instance = new PackageStorage();
		return *instance;
	}
	else {
		return *instance;
	}
}

PackageStorage::PackageStorage()
{
}

PackageStorage::~PackageStorage()
{
}

const Paquet *PackageStorage::getReceivedPackage() const {
	return received.empty() ? nullptr : received.front();
}

const PaquetPlayerCoord *PackageStorage::getPlayersPackage() const {
	return players.empty() ? nullptr : (const PaquetPlayerCoord *)players.front();
}

const PaquetPlayerCoord *PackageStorage::getEnemiesPackage() const {
	return enemies.empty() ? nullptr : (const PaquetPlayerCoord *)enemies.front();
}

const PaquetObstacle *PackageStorage::getObstaclesPackage() const {
	return obstacles.empty() ? nullptr : (const PaquetObstacle *)obstacles.front();
}

const PaquetPlayerShot * PackageStorage::getShotsPackage() const
{
	return shots.empty() ? nullptr : (const PaquetPlayerShot *)shots.front();
}

const Paquet * PackageStorage::getToSendPackage() const
{
	return toSend.empty() ? nullptr : (const Paquet *)toSend.front();
}

const PaquetListParties * PackageStorage::getGameListPackage() const
{
	return gameList.empty() ? nullptr : (const PaquetListParties *)gameList.front();
}

const PaquetListPlayers * PackageStorage::getPlayerListPackage() const
{
	return playerList.empty() ? nullptr : (const PaquetListPlayers *)playerList.front();
}

const PaquetResponse * PackageStorage::getAnswersPackage() const
{
	return answers.empty() ? nullptr : (const PaquetResponse *)answers.front();
}

const PaquetLaunch * PackageStorage::getLaunchPackage() const
{
	return launch.empty() ? nullptr : (const PaquetLaunch *)launch.front();
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

void PackageStorage::storeGameListPackage(Paquet * package)
{
	gameList.push_back(package);
}

void PackageStorage::storePlayerListPackage(Paquet * package)
{
	playerList.push_back(package);
}

void PackageStorage::storeAnswersPackage(Paquet * package)
{
	answers.push_back(package);
}

void PackageStorage::storeLaunchPackage(Paquet * package)
{
	launch.push_back(package);
}

void PackageStorage::deleteReceivedPackage()
{
	received.erase(received.begin());
}

void PackageStorage::deletePlayersPackage()
{
	players.erase(players.begin());
}

void PackageStorage::deleteEnemiesPackage()
{
	enemies.erase(enemies.begin());
}

void PackageStorage::deleteObstaclesPackage()
{
	obstacles.erase(obstacles.begin());
}

void PackageStorage::deleteShotsPackage()
{
	shots.erase(shots.begin());
}

void PackageStorage::deleteToSendPackage()
{
	toSend.erase(toSend.begin());
}

void PackageStorage::deleteGameListPackage()
{
	gameList.erase(gameList.begin());
}

void PackageStorage::deletePlayerListPackage()
{
	playerList.erase(playerList.begin());
}

void PackageStorage::deleteAnswersPackage()
{
	answers.erase(answers.begin());
}

void PackageStorage::deleteLaunchPackage()
{
	launch.erase(launch.begin());
}

bool PackageStorage::isThereReceivedPackage()
{
	return !received.empty();
}

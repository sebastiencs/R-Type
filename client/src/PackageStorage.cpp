#include "PackageStorage.hh"

PackageStorage & PackageStorage::getInstance()
{
	static PackageStorage *instance = nullptr;
	if (instance == nullptr) {
		instance = new PackageStorage();
	}
	return *instance;
}

PackageStorage::PackageStorage()
  : _semOut(new Semaphore()),
    _semIn(new Semaphore())
{
}

PackageStorage::~PackageStorage()
{
}

const Paquet *PackageStorage::getReceivedPackage() const {
	return received.empty() ? nullptr : received.front();
}

const PaquetPlayerCoord *PackageStorage::getPlayersPackage() const {
	return players.empty() ? nullptr : players.front();
}

const PaquetPlayerCoord *PackageStorage::getEnemiesPackage() const {
	return enemies.empty() ? nullptr : enemies.front();
}

const PaquetObstacle *PackageStorage::getObstaclesPackage() const {
	return obstacles.empty() ? nullptr : obstacles.front();
}

const PaquetPlayerShot * PackageStorage::getShotsPackage() const
{
	return shots.empty() ? nullptr : shots.front();
}

const Paquet * PackageStorage::getToSendUDPPackage() const
{
	return toSendUDP.empty() ? nullptr : toSendUDP.front();
}

const Paquet * PackageStorage::getToSendTCPPackage() const
{
	return toSendTCP.empty() ? nullptr : toSendTCP.front();
}

const PaquetListParties * PackageStorage::getGameListPackage() const
{
	return gameList.empty() ? nullptr : gameList.front();
}

const PaquetListPlayers * PackageStorage::getPlayerListPackage() const
{
	return playerList.empty() ? nullptr : playerList.front();
}

const PaquetResponse * PackageStorage::getAnswersPackage() const
{
	return answers.empty() ? nullptr : answers.front();
}

const PaquetLaunch * PackageStorage::getLaunchPackage() const
{
	return launch.empty() ? nullptr : launch.front();
}

void PackageStorage::storeReceivedPackage(Paquet * package)
{
	received.push_back(package);
	_semIn->post();
}

void PackageStorage::storePlayersPackage(PaquetPlayerCoord * package)
{
	players.push_back(package);
}

void PackageStorage::storeEnemiesPackage(PaquetPlayerCoord * package)
{
	enemies.push_back(package);
}

void PackageStorage::storeObstaclesPackage(PaquetObstacle * package)
{
	obstacles.push_back(package);
}

void PackageStorage::storeShotsPackage(PaquetPlayerShot * package)
{
	shots.push_back(package);
}

void PackageStorage::storeToSendUDPPackage(Paquet * package)
{
	toSendUDP.push_back(package);
	_semOut->post();
}

void PackageStorage::storeToSendTCPPackage(Paquet * package)
{
	toSendTCP.push_back(package);
	_semOut->post();
}

void PackageStorage::storeGameListPackage(PaquetListParties * package)
{
	gameList.push_back(package);
}

void PackageStorage::storePlayerListPackage(PaquetListPlayers * package)
{
	playerList.push_back(package);
}

void PackageStorage::storeAnswersPackage(PaquetResponse * package)
{
	answers.push_back(package);
}

void PackageStorage::storeLaunchPackage(PaquetLaunch * package)
{
	launch.push_back(package);
}

void PackageStorage::deleteReceivedPackage()
{
	delete received.front();
	received.erase(received.begin());

}

void PackageStorage::deletePlayersPackage()
{
	delete players.front();
	players.erase(players.begin());
}

void PackageStorage::deleteEnemiesPackage()
{
	delete enemies.front();
	enemies.erase(enemies.begin());
}

void PackageStorage::deleteObstaclesPackage()
{
	delete obstacles.front();
	obstacles.erase(obstacles.begin());
}

void PackageStorage::deleteShotsPackage()
{
	delete shots.front();
	shots.erase(shots.begin());
}

void PackageStorage::deleteToSendUDPPackage()
{
	delete toSendUDP.front();
	toSendUDP.erase(toSendUDP.begin());
}

void PackageStorage::deleteToSendTCPPackage()
{
	delete toSendTCP.front();
	toSendTCP.erase(toSendTCP.begin());
}

void PackageStorage::deleteGameListPackage()
{
	delete gameList.front();
	gameList.erase(gameList.begin());
}

void PackageStorage::deletePlayerListPackage()
{
	delete playerList.front();
	playerList.erase(playerList.begin());
}

void PackageStorage::deleteAnswersPackage()
{
	delete answers.front();
	answers.erase(answers.begin());
}

void PackageStorage::deleteLaunchPackage()
{
	delete launch.front();
	launch.erase(launch.begin());
}

bool PackageStorage::isThereReceivedPackage()
{
	return !received.empty();
}

void PackageStorage::waitForReceivedPackage()
{
  _semIn->wait();
}

void PackageStorage::waitForPackage()
{
  _semOut->wait();
}

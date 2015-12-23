#include "PackageStorage.hh"
#include "Debug.hh"
#include "IOEvent.hh"

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
	return received.empty() ? nullptr : received.front().get();
}

const PaquetPlayerCoord *PackageStorage::getPlayersPackage() const {
	if (!players.empty())
		DEBUG_MSG(*players.front());
	return players.empty() ? nullptr : players.front();
}

// const PaquetPlayerCoord *PackageStorage::getEnemiesPackage() const {
// 	if (!obstacles.empty())
// 		DEBUG_MSG(*enemies.front());
// 	return enemies.empty() ? nullptr : enemies.front();
// }

const PaquetObstacle *PackageStorage::getObstaclesPackage() const {
	if (!obstacles.empty())
		DEBUG_MSG(*obstacles.front());
	return obstacles.empty() ? nullptr : obstacles.front();
}

const PaquetPlayerShot * PackageStorage::getShotsPackage() const {
	if (!shots.empty())
		DEBUG_MSG(*shots.front());
	return shots.empty() ? nullptr : shots.front();
}

const PaquetReady * PackageStorage::getReadyPackage() const
{
	return ready.empty() ? nullptr : ready.front();
}

const Paquet * PackageStorage::getToSendUDPPackage() const {
	return toSendUDP.empty() ? nullptr : toSendUDP.front();
}

const Paquet * PackageStorage::getToSendTCPPackage() const {
	return toSendTCP.empty() ? nullptr : toSendTCP.front();
}

const PaquetListParties * PackageStorage::getGameListPackage() const {
	if (!gameList.empty())
		DEBUG_MSG(*gameList.front());
	return gameList.empty() ? nullptr : gameList.front();
}

const PaquetListPlayers * PackageStorage::getPlayerListPackage() const {
	if (!playerList.empty())
		DEBUG_MSG(*playerList.front());
	return playerList.empty() ? nullptr : playerList.front();
}

const PaquetResponse * PackageStorage::getAnswersPackage() const {
	if (!answers.empty())
		DEBUG_MSG(*answers.front());
	return answers.empty() ? nullptr : answers.front();
}

const PaquetLaunch * PackageStorage::getLaunchPackage() const {
	if (!launch.empty())
		DEBUG_MSG(*launch.front());
	return launch.empty() ? nullptr : launch.front();
}

const PaquetLeave * PackageStorage::getLeavePackage() const {
	if (!leave.empty())
		DEBUG_MSG(*leave.front());
	return leave.empty() ? nullptr : leave.front();
}

const PaquetEnemy * PackageStorage::getEnemyPackage() const {
	if (!enemy.empty())
		DEBUG_MSG(*enemy.front());
	return enemy.empty() ? nullptr : enemy.front().get();
}

const PaquetBonusMalus * PackageStorage::getBonusMalusPackage() const {
	if (!bonusmalus.empty())
		DEBUG_MSG(*bonusmalus.front());
	return bonusmalus.empty() ? nullptr : bonusmalus.front();
}

const PaquetLife * PackageStorage::getLifePackage() const {
	if (!life.empty())
		DEBUG_MSG(*life.front());
	return life.empty() ? nullptr : life.front();
}

const PaquetDeath * PackageStorage::getDeathPackage() const {
	if (!death.empty())
		DEBUG_MSG(*death.front());
	return death.empty() ? nullptr : death.front();
}

const PaquetAttrBonus * PackageStorage::getAttrBonusPackage() const {
	if (!attrbonus.empty())
		DEBUG_MSG(*attrbonus.front());
	return attrbonus.empty() ? nullptr : attrbonus.front();
}

void PackageStorage::storeReceivedPackage(Paquet_SharedPtr package) {
	received.push_back(package);
	_semIn->post();
}

void PackageStorage::storePlayersPackage(PaquetPlayerCoord * package)
{
	players.push_back(package);
}

// void PackageStorage::storeEnemiesPackage(PaquetPlayerCoord * package)
// {
// 	enemies.push_back(package);
// }

void PackageStorage::storeObstaclesPackage(PaquetObstacle * package)
{
	obstacles.push_back(package);
}

void PackageStorage::storeShotsPackage(PaquetPlayerShot * package)
{
	shots.push_back(package);
}

void PackageStorage::storeReadyPackage(PaquetReady * package)
{
	ready.push_back(package);
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

void PackageStorage::storeLeavePackage(PaquetLeave * package)
{
	leave.push_back(package);
}

void PackageStorage::storeEnemyPackage(PaquetEnemy_SharedPtr package)
{
	enemy.push_back(package);
}

void PackageStorage::storeBonusMalusPackage(PaquetBonusMalus * package)
{
	bonusmalus.push_back(package);
}

void PackageStorage::storeLifePackage(PaquetLife * package)
{
	life.push_back(package);
}

void PackageStorage::storeDeathPackage(PaquetDeath * package)
{
	death.push_back(package);
}

void PackageStorage::storeAttrBonusPackage(PaquetAttrBonus * package)
{
	attrbonus.push_back(package);
}

void PackageStorage::deleteReceivedPackage()
{
  if (!received.empty()) {
    received.pop_front();
//    delete received.front();
//    received.erase(received.begin());
  }
}

void PackageStorage::deletePlayersPackage()
{
  if (!players.empty()) {
    delete players.front();
    players.erase(players.begin());
  }
}

// void PackageStorage::deleteEnemiesPackage()
// {
//   if (!enemies.empty()) {
//     delete enemies.front();
//     enemies.erase(enemies.begin());
//   }
// }

void PackageStorage::deleteObstaclesPackage()
{
  if (!obstacles.empty()) {
    delete obstacles.front();
    obstacles.erase(obstacles.begin());
  }
}

void PackageStorage::deleteShotsPackage()
{
  if (!shots.empty()) {
    delete shots.front();
    shots.erase(shots.begin());
  }
}

void PackageStorage::deleteReadyPackage()
{
  if (!ready.empty()) {
    delete ready.front();
    ready.erase(ready.begin());
  }
}

void PackageStorage::deleteToSendUDPPackage()
{
  if (!toSendUDP.empty()) {
    delete toSendUDP.front();
    toSendUDP.erase(toSendUDP.begin());
  }
}

void PackageStorage::deleteToSendTCPPackage()
{
  if (!toSendTCP.empty()) {
    delete toSendTCP.front();
    toSendTCP.erase(toSendTCP.begin());
  }
}

void PackageStorage::deleteGameListPackage()
{
  if (!gameList.empty()) {
    delete gameList.front();
    gameList.erase(gameList.begin());
  }
}

void PackageStorage::deletePlayerListPackage()
{
  if (!playerList.empty()) {
    delete playerList.front();
    playerList.erase(playerList.begin());
  }
}

void PackageStorage::deleteAnswersPackage()
{
  if (!answers.empty()) {
    delete answers.front();
    answers.erase(answers.begin());
  }
}

void PackageStorage::deleteLaunchPackage()
{
  if (!launch.empty()) {
    delete launch.front();
    launch.erase(launch.begin());
  }
}

void PackageStorage::deleteEnemyPackage()
{
  if (!enemy.empty()) {
    //delete enemy.front();
    enemy.pop_front();
//    enemy.erase(enemy.begin());
  }
}

void PackageStorage::deleteLeavePackage()
{
  if (!leave.empty()) {
    delete leave.front();
    leave.erase(leave.begin());
  }
}

void PackageStorage::deleteBonusMalusPackage()
{
  if (!bonusmalus.empty()) {
    delete bonusmalus.front();
    bonusmalus.erase(bonusmalus.begin());
  }
}

void PackageStorage::deleteLifePackage()
{
  if (!life.empty()) {
    delete life.front();
    life.erase(life.begin());
  }
}

void PackageStorage::deleteDeathPackage()
{
  if (!death.empty()) {
    delete death.front();
    death.erase(death.begin());
  }
}

void PackageStorage::deleteAttrBonusPackage()
{
  if (!attrbonus.empty()) {
    delete attrbonus.front();
    attrbonus.erase(attrbonus.begin());
  }
}

bool PackageStorage::isThereReceivedPackage()
{
	return !received.empty();
}

void PackageStorage::waitForReceivedPackage()
{
  if (_semIn->tryWait() == false) {
    IOEvent::wait(5);
  }
}

bool PackageStorage::waitForPackage()
{
  if (_semOut->tryWait() == false) {
    IOEvent::wait(5);
    if (_semOut->tryWait() == true) {
      return (true);
    }
    else {
      return (false);
    }
  }
  return (true);
  // _semOut->wait();
}

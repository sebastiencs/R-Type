#include "PackageStorage.hh"
#include "Debug.hh"
#include "IOEvent.hh"

PackageStorage *PackageStorage::me = nullptr;

PackageStorage & PackageStorage::getInstance()
{
  // struct MakeShared : public PackageStorage { };

  // static PackageStorage_SharedPtr instance = nullptr;

  // if (instance == nullptr) {
  //   instance = std::make_shared<MakeShared>();
  // }

  // return *instance;

  return (*me);
}

PackageStorage::PackageStorage()
  : _semOut(std::make_unique<Semaphore>()),
    _semIn(std::make_unique<Semaphore>())
{
  if (me == nullptr) {
    me = this;
  }
}

PackageStorage::~PackageStorage()
{
  std::cerr << "DESTRUCTOR" << std::endl;
}

const Paquet_SharedPtr PackageStorage::getReceivedPackage() const {
	return received.empty() ? nullptr : received.front();
}

const PaquetPlayerCoord_SharedPtr PackageStorage::getPlayersPackage() const {
	if (!players.empty())
		DEBUG_MSG(*players.front());
	return players.empty() ? nullptr : players.front();
}

const PaquetObstacle_SharedPtr PackageStorage::getObstaclesPackage() const {
	if (!obstacles.empty())
		DEBUG_MSG(*obstacles.front());
	return obstacles.empty() ? nullptr : obstacles.front();
}

const PaquetPlayerShot_SharedPtr  PackageStorage::getShotsPackage() const {
	if (!shots.empty())
		DEBUG_MSG(*shots.front());
	return shots.empty() ? nullptr : shots.front();
}

const PaquetReady_SharedPtr  PackageStorage::getReadyPackage() const
{
	return ready.empty() ? nullptr : ready.front();
}

const Paquet_SharedPtr PackageStorage::getToSendUDPPackage() const {
	return toSendUDP.empty() ? nullptr : toSendUDP.front();
}

const Paquet_SharedPtr PackageStorage::getToSendTCPPackage() const {
	return toSendTCP.empty() ? nullptr : toSendTCP.front();
}

const PaquetListParties_SharedPtr  PackageStorage::getGameListPackage() const {
	if (!gameList.empty())
		DEBUG_MSG(*gameList.front());
	return gameList.empty() ? nullptr : gameList.front();
}

const PaquetListPlayers_SharedPtr  PackageStorage::getPlayerListPackage() const {
	if (!playerList.empty())
		DEBUG_MSG(*playerList.front());
	return playerList.empty() ? nullptr : playerList.front();
}

const PaquetResponse_SharedPtr  PackageStorage::getAnswersPackage() const {
	if (!answers.empty())
		DEBUG_MSG(*answers.front());
	return answers.empty() ? nullptr : answers.front();
}

const PaquetLaunch_SharedPtr  PackageStorage::getLaunchPackage() const {
	if (!launch.empty())
		DEBUG_MSG(*launch.front());
	return launch.empty() ? nullptr : launch.front();
}

const PaquetLeave_SharedPtr  PackageStorage::getLeavePackage() const {
	if (!leave.empty())
		DEBUG_MSG(*leave.front());
	return leave.empty() ? nullptr : leave.front();
}

const PaquetEnemy_SharedPtr  PackageStorage::getEnemyPackage() const {
	if (!enemy.empty())
		DEBUG_MSG(*enemy.front());
	return enemy.empty() ? nullptr : enemy.front();
}

const PaquetBonusMalus_SharedPtr  PackageStorage::getBonusMalusPackage() const {
	if (!bonusmalus.empty())
		DEBUG_MSG(*bonusmalus.front());
	return bonusmalus.empty() ? nullptr : bonusmalus.front();
}

const PaquetLife_SharedPtr  PackageStorage::getLifePackage() const {
	if (!life.empty())
		DEBUG_MSG(*life.front());
	return life.empty() ? nullptr : life.front();
}

const PaquetDeath_SharedPtr  PackageStorage::getDeathPackage() const {
	if (!death.empty())
		DEBUG_MSG(*death.front());
	return death.empty() ? nullptr : death.front();
}

const PaquetAttrBonus_SharedPtr  PackageStorage::getAttrBonusPackage() const {
	if (!attrbonus.empty())
		DEBUG_MSG(*attrbonus.front());
	return attrbonus.empty() ? nullptr : attrbonus.front();
}

void PackageStorage::storeReceivedPackage(Paquet_SharedPtr package) {
	received.push_back(package);
	_semIn->post();
}

void PackageStorage::storePlayersPackage(PaquetPlayerCoord_SharedPtr package)
{
	players.push_back(package);
}

// void PackageStorage::storeEnemiesPackage(PaquetPlayerCoord_SharedPtr package)
// {
// 	enemies.push_back(package);
// }

void PackageStorage::storeObstaclesPackage(PaquetObstacle_SharedPtr package)
{
	obstacles.push_back(package);
}

void PackageStorage::storeShotsPackage(PaquetPlayerShot_SharedPtr package)
{
	shots.push_back(package);
}

void PackageStorage::storeReadyPackage(PaquetReady_SharedPtr package)
{
	ready.push_back(package);
}

void PackageStorage::storeToSendUDPPackage(Paquet_SharedPtr package)
{
	toSendUDP.push_back(package);
	_semOut->post();
}

void PackageStorage::storeToSendTCPPackage(Paquet_SharedPtr package)
{
	toSendTCP.push_back(package);
	_semOut->post();
}

void PackageStorage::storeGameListPackage(PaquetListParties_SharedPtr package)
{
	gameList.push_back(package);
}

void PackageStorage::storePlayerListPackage(PaquetListPlayers_SharedPtr package)
{
	playerList.push_back(package);
}

void PackageStorage::storeAnswersPackage(PaquetResponse_SharedPtr package)
{
	answers.push_back(package);
}

void PackageStorage::storeLaunchPackage(PaquetLaunch_SharedPtr package)
{
	launch.push_back(package);
}

void PackageStorage::storeLeavePackage(PaquetLeave_SharedPtr package)
{
	leave.push_back(package);
}

void PackageStorage::storeEnemyPackage(PaquetEnemy_SharedPtr package)
{
	enemy.push_back(package);
}

void PackageStorage::storeBonusMalusPackage(PaquetBonusMalus_SharedPtr package)
{
	bonusmalus.push_back(package);
}

void PackageStorage::storeLifePackage(PaquetLife_SharedPtr package)
{
	life.push_back(package);
}

void PackageStorage::storeDeathPackage(PaquetDeath_SharedPtr package)
{
	death.push_back(package);
}

void PackageStorage::storeAttrBonusPackage(PaquetAttrBonus_SharedPtr package)
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
    players.pop_front();
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
    obstacles.pop_front();
  }
}

void PackageStorage::deleteShotsPackage()
{
  if (!shots.empty()) {
    shots.pop_front();
  }
}

void PackageStorage::deleteReadyPackage()
{
  if (!ready.empty()) {
    ready.pop_front();
  }
}

void PackageStorage::deleteToSendUDPPackage()
{
  if (!toSendUDP.empty()) {
    toSendUDP.pop_front();
  }
}

void PackageStorage::deleteToSendTCPPackage()
{
  if (!toSendTCP.empty()) {
    toSendTCP.pop_front();
  }
}

void PackageStorage::deleteGameListPackage()
{
  if (!gameList.empty()) {
    gameList.pop_front();
  }
}

void PackageStorage::deletePlayerListPackage()
{
  if (!playerList.empty()) {
    playerList.pop_front();
  }
}

void PackageStorage::deleteAnswersPackage()
{
  if (!answers.empty()) {
    answers.pop_front();
  }
}

void PackageStorage::deleteLaunchPackage()
{
  if (!launch.empty()) {
    launch.pop_front();
  }
}

void PackageStorage::deleteEnemyPackage()
{
  if (!enemy.empty()) {
    enemy.pop_front();
  }
}

void PackageStorage::deleteLeavePackage()
{
  if (!leave.empty()) {
    leave.pop_front();
  }
}

void PackageStorage::deleteBonusMalusPackage()
{
  if (!bonusmalus.empty()) {
    bonusmalus.pop_front();
  }
}

void PackageStorage::deleteLifePackage()
{
  if (!life.empty()) {
    life.pop_front();
  }
}

void PackageStorage::deleteDeathPackage()
{
  if (!death.empty()) {
    death.pop_front();
  }
}

void PackageStorage::deleteAttrBonusPackage()
{
  if (!attrbonus.empty()) {
    attrbonus.pop_front();
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

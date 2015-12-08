#include "Packager.hh"

Packager::Packager()
{
}

Packager::~Packager()
{
}

void Packager::createMovementPackage(uint8_t _playerID, uint16_t _x, uint16_t _y)
{
	PaquetPlayerCoord *movement = new PaquetPlayerCoord();
	movement->setPlayerID(_playerID);
	movement->setPosition(_x, _y);
	movement->createPaquet();
	PackageStorage::getInstance().storeToSendUDPPackage(movement);
}

void Packager::createShotPackage(uint8_t _playerID, uint8_t _type, uint16_t _x, uint16_t _y)
{
	PaquetPlayerShot *shot = new PaquetPlayerShot();
	shot->setPlayerID(_playerID);
	shot->setType(_type);
	shot->setPosition(_x, _y);
	shot->createPaquet();
	PackageStorage::getInstance().storeToSendUDPPackage(shot);
}

void Packager::createGameListPackage()
{
	std::cout << "Request Create" << std::endl;
	PaquetRequestParties *request = new PaquetRequestParties();
	request->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(request);
}

void Packager::createPlayerListPackage()
{
	PaquetRequestPlayers *request = new PaquetRequestPlayers();
	request->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(request);
}

void Packager::createJoinPartyPackage(std::string _name)
{
	PaquetJoinParty *join = new PaquetJoinParty();
	join->setName(_name);
	join->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(join);
}

void Packager::createCreatePartyPackage(std::string	_name)
{
	PaquetCreateParty *create = new PaquetCreateParty();
	create->setName(_name);
	create->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(create);
}

void Packager::createReadyPackage(uint8_t _playerID, uint8_t _ready)
{
	PaquetReady *ready = new PaquetReady();
	ready->setID(_playerID);
	ready->setStatus(_ready);
	ready->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(ready);
}

void Packager::createLeavePackage(uint8_t _playerID)
{
	PaquetLeave *leave = new PaquetLeave();
	leave->setID(_playerID);
	leave->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(leave);
}

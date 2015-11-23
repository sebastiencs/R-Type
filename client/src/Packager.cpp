#include "Packager.hh"

Packager::Packager()
{
}

Packager::~Packager()
{
}

void Packager::createMovementPackage(uint8_t _playerID, uint8_t _x, uint8_t _y)
{
	PaquetPlayerCoord *movement = new PaquetPlayerCoord();
	movement->setPlayerID(_playerID);
	movement->setPosition(_x, _y);
	movement->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(movement);
}

void Packager::createShotPackage(uint8_t _playerID, uint8_t _type, uint8_t _x, uint8_t _y)
{
	PaquetPlayerShot *shot = new PaquetPlayerShot();
	shot->setPlayerID(_playerID);
	shot->setType(_type);
	shot->setPosition(_x, _y);
	shot->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(shot);
}

void Packager::createGameListPackage()
{
	PaquetRequestParties *request = new PaquetRequestParties();
	request->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(request);
}

void Packager::createPlayerListPackage()
{
	PaquetRequestPlayers *request = new PaquetRequestPlayers();
	request->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(request);
}

void Packager::createJoinPartyPackage(std::string _name)
{
	PaquetJoinParty *join = new PaquetJoinParty();
	join->setName(_name);
	join->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(join);
}

void Packager::createCreatePartyPackage(std::string	_name)
{
	PaquetCreateParty *create = new PaquetCreateParty();
	create->setName(_name);
	create->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(create);
}

void Packager::createReadyPackage(uint8_t _playerID)
{
	PaquetReady *ready = new PaquetReady();
	ready->setID(_playerID);
	ready->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(ready);
}

void Packager::createLeavePackage(uint8_t _playerID)
{
	PaquetLeave *leave = new PaquetLeave();
	leave->setID(_playerID);
	leave->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(leave);
}


#include "Packager.hh"

Packager::Packager(PackageStorage *_storage)
{
	storage = _storage;
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
	storage->storeToSendPackage(movement);
}

void Packager::createShotPackage(uint8_t _playerID, uint8_t _type, uint8_t _x, uint8_t _y)
{
	PaquetPlayerShot *shot = new PaquetPlayerShot();
	shot->setPlayerID(_playerID);
	shot->setType(_type);
	shot->setPosition(_x, _y);
	shot->createPaquet();
	storage->storeToSendPackage(shot);
}

void Packager::createGameListPackage()
{
	PaquetRequestParties *request = new PaquetRequestParties();
	request->createPaquet();
	storage->storeToSendPackage(request);
}

void Packager::createPlayerListPackage()
{
	PaquetRequestPlayers *request = new PaquetRequestPlayers();
	request->createPaquet();
	storage->storeToSendPackage(request);
}

void Packager::createJoinPartyPackage(std::string _name)
{
	PaquetJoinParty *join = new PaquetJoinParty();
	join->setName(_name);
	join->createPaquet();
	storage->storeToSendPackage(join);
}

void Packager::createCreatePartyPackage(std::string	_name)
{
	PaquetCreateParty *create = new PaquetCreateParty();
	create->setName(_name);
	create->createPaquet();
	storage->storeToSendPackage(create);
}

void Packager::createReadyPackage(uint8_t _playerID)
{
	PaquetReady *ready = new PaquetReady();
	ready->setID(_playerID);
	ready->createPaquet();
	storage->storeToSendPackage(ready);
}

void Packager::createLeavePackage(uint8_t _playerID)
{
	PaquetLeave *leave = new PaquetLeave();
	leave->setID(_playerID);
	leave->createPaquet();
	storage->storeToSendPackage(leave);
}


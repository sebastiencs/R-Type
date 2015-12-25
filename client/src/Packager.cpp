#include "Packager.hh"

Packager::Packager()
{
}

Packager::~Packager()
{
}

void Packager::createMovementPackage(uint8_t _playerID, uint16_t _x, uint16_t _y)
{
	auto &&movement = std::make_shared<PaquetPlayerCoord>();
	movement->setPlayerID(_playerID);
	movement->setPosition(_x, _y);
	movement->createPaquet();
	PackageStorage::getInstance().storeToSendUDPPackage(movement);
}

void Packager::createChatPackage(uint8_t id, const std::string &message)
{
	auto &&chat = std::make_shared<PaquetChat>();
	chat->setID(id);
	chat->setMessage(message);
	chat->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(chat);
}

void Packager::createFirstUDPPackage(uint8_t _playerID)
{
  	auto &&first = std::make_shared<PaquetFirstUDP>();
  	first->setId(_playerID);
  	first->createPaquet();
  	PackageStorage::getInstance().storeToSendUDPPackage(first);
}

void Packager::createShotPackage(uint8_t _playerID, uint8_t _type, uint16_t speed, uint16_t _x, uint16_t _y)
{
	auto &&shot = std::make_shared<PaquetPlayerShot>();
	shot->setPlayerID(_playerID);
	shot->setType(_type);
	shot->setPosition(_x, _y);
	shot->setSpeed(speed);
	shot->createPaquet();
	PackageStorage::getInstance().storeToSendUDPPackage(shot);
}

void Packager::createGameListPackage()
{
	std::cout << "Request Create" << std::endl;
	auto &&request = std::make_shared<PaquetRequestParties>();
	request->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(request);
}

void Packager::createPlayerListPackage()
{
	auto &&request = std::make_shared<PaquetRequestPlayers>();
	request->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(request);
}

void Packager::createJoinPartyPackage(std::string _name)
{
	auto &&join = std::make_shared<PaquetJoinParty>();
	join->setName(_name);
	join->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(join);
}

void Packager::createCreatePartyPackage(std::string	_name)
{
	auto &&create = std::make_shared<PaquetCreateParty>();
	create->setName(_name);
	create->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(create);
}

void Packager::createReadyPackage(uint8_t _playerID, uint8_t _ready)
{
	auto &&ready = std::make_shared<PaquetReady>();
	ready->setID(_playerID);
	ready->setStatus(_ready);
	ready->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(ready);
}

void Packager::createLeavePackage(uint8_t _playerID)
{
	auto &&leave = std::make_shared<PaquetLeave>();
	leave->setID(_playerID);
	leave->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(leave);
}

#ifndef PACKAGER_HH
#define PACKAGER_HH

#include <stdint.h>
#include "PaquetPlayerCoord.hh"
#include "PaquetPlayerShot.hh"
#include "PackageStorage.hh"
#include "PaquetRequestParties.hh"
#include "PaquetRequestPlayers.hh"
#include "PaquetJoinParty.hh"
#include "PaquetCreateParty.hh"
#include "PaquetReady.hh"
#include "PaquetLeave.hh"

class Packager {
public:
	Packager();
	virtual ~Packager();

	static void createMovementPackage(const uint8_t _playerID, const uint16_t _x, const uint16_t _y);
	static void createShotPackage(const uint8_t _playerID, const uint8_t _type, const uint16_t speed, const uint16_t _x, const uint16_t _y);

	static void createChatPackage(const uint8_t id, const std::string &message);

	static void createGameListPackage();
	static void createPlayerListPackage();

	static void createJoinPartyPackage(const std::string &_name);
	static void createCreatePartyPackage(const std::string &_name);

	static void createReadyPackage(const uint8_t _playerID, const uint8_t _ready);
	static void createLeavePackage(const uint8_t _playerID);

	static void createFirstUDPPackage(const uint8_t _playerID);
};

using Packager_SharedPtr = std::shared_ptr<Packager>;

#endif // !PACKAGER_HH

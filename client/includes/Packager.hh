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

	static void createMovementPackage(uint8_t _playerID, uint16_t _x,	uint16_t _y);
	static void createShotPackage(uint8_t _playerID, uint8_t _type, uint16_t _x, uint16_t _y);

	static void createGameListPackage();
	static void createPlayerListPackage();

	static void createJoinPartyPackage(std::string	_name);
	static void createCreatePartyPackage(std::string _name);

	static void createReadyPackage(uint8_t	_playerID, uint8_t _ready);
	static void createLeavePackage(uint8_t	_playerID);
};

#endif // !PACKAGER_HH

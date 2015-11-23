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

	void createMovementPackage(uint8_t _playerID, uint8_t _x,	uint8_t _y);
	void createShotPackage(uint8_t _playerID, uint8_t _type, uint8_t _x, uint8_t _y);
	
	void createGameListPackage();
	void createPlayerListPackage();

	void createJoinPartyPackage(std::string	_name);
	void createCreatePartyPackage(std::string _name);

	void createReadyPackage(uint8_t	_playerID);
	void createLeavePackage(uint8_t	_playerID);
};

#endif // !PACKAGER_HH

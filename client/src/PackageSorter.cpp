//
// PackageSorter.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 02:08:19 2015 chapui_s
// Last update Sun Nov 15 02:08:19 2015 chapui_s
//

#include "PackageSorter.hh"
#include "Paquets.hh"
#include "Debug.hh"

PackageSorter::PackageSorter()
  : cond (1)
{
	_tab[0] = [this](Paquet_SharedPtr paquet UNUSED) {};
	_tab[1] = [this](Paquet_SharedPtr paquet UNUSED) {};
	_tab[2] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetListParties>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeGameListPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[3] = [this](Paquet_SharedPtr paquet UNUSED) {};
	_tab[4] = [this](Paquet_SharedPtr paquet UNUSED) {};
	_tab[5] = [this](Paquet_SharedPtr paquet UNUSED) {};
	_tab[6] = [this](Paquet_SharedPtr paquet UNUSED) {
		auto &&store = std::make_shared<PaquetListPlayers>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storePlayerListPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[7] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetPlayerCoord>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storePlayersPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[8] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetPlayerShot>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeShotsPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[9] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetObstacle>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeObstaclesPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[10] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetReady>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeReadyPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[11] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetLaunch>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeLaunchPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[12] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetLeave>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeLeavePackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[14] = [this](Paquet_SharedPtr paquet) {
		auto store = std::make_shared<PaquetEnemy>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeEnemyPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[15] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetBonusMalus>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeBonusMalusPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[16] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetLife>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeLifePackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[17] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetDeath>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeDeathPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[18] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetAttrBonus>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeAttrBonusPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[19] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetRename>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeRenamePackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[20] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetChat>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeChatPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[0xFF] = [this](Paquet_SharedPtr paquet) {
		auto &&store = std::make_shared<PaquetResponse>(paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeAnswersPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};

	Callback_t fptr = [this](void *c) {this->sortPaquet(c); return nullptr; };
	thread = std::make_shared<Thread>(fptr, &cond);
}

PackageSorter::~PackageSorter()
{
	cond = 0;
	thread->join();
}

void PackageSorter::sortPaquet(void *c)
{
  int *condition = reinterpret_cast<int *>(c);

  while (*condition)
  {
    PackageStorage::getInstance().waitForReceivedPackage();

    auto &&paquet = PackageStorage::getInstance().getReceivedPackage();

    if (paquet) {
      auto it = _tab.find(paquet->getData()[0]);

      if (it != _tab.end()) {
        it->second(paquet);
      }
      else {
        std::cerr << "Unknown paquet" << std::endl;
      }
    }
  }
}

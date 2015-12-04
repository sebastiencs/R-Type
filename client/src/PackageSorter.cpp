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
{
	_tab[0] = [this](Paquet *paquet UNUSED) {};
	_tab[1] = [this](Paquet *paquet UNUSED) {};
	_tab[2] = [this](Paquet *paquet) {
		PaquetListParties *store = new PaquetListParties((void *)paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeGameListPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[3] = [this](Paquet *paquet UNUSED) {};
	_tab[4] = [this](Paquet *paquet UNUSED) {};
	_tab[5] = [this](Paquet *paquet UNUSED) {};
	_tab[6] = [this](Paquet *paquet UNUSED) {
		PaquetListPlayers *store = new PaquetListPlayers((void *)paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storePlayerListPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[7] = [this](Paquet *paquet) {
		PaquetPlayerCoord *store = new PaquetPlayerCoord((void *)paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storePlayersPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[8] = [this](Paquet *paquet) {
		PaquetPlayerShot *store = new PaquetPlayerShot((void *)paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeShotsPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[9] = [this](Paquet *paquet) {
		PaquetObstacle *store = new PaquetObstacle((void *)paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeObstaclesPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	_tab[10] = [this](Paquet *paquet UNUSED) {};
	_tab[11] = [this](Paquet *paquet UNUSED) {};
	_tab[12] = [this](Paquet *paquet UNUSED) {};
	_tab[0xFF] = [this](Paquet *paquet) {
		PaquetResponse *store = new PaquetResponse((void *)paquet->getData(), paquet->getSize());
		PackageStorage::getInstance().storeAnswersPackage(store);
		PackageStorage::getInstance().deleteReceivedPackage();
	};

	Callback_t fptr = [this](void *) {this->sortPaquet(); return nullptr; };
	thread = new Thread(fptr, nullptr);
}

PackageSorter::~PackageSorter()
{
	thread->close();
	delete thread;
}

void PackageSorter::sortPaquet()
{
  while (1)
  {
    PackageStorage::getInstance().waitForReceivedPackage();

    const Paquet *paquet = PackageStorage::getInstance().getReceivedPackage();

    auto it = _tab.find(paquet->getData()[0]);

    if (it != _tab.end()) {
      it->second(const_cast<Paquet*>(paquet));
    }
    else {
      std::cerr << "Unknown paquet" << std::endl;
    }
  }
}

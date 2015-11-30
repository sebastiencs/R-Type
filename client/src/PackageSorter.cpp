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
#include "Debug.hh"

PackageSorter::PackageSorter()
{
	tab[0] = [this](Paquet *paquet UNUSED) {};
	tab[1] = [this](Paquet *paquet UNUSED) {};
	tab[2] = [this](Paquet *paquet) {
		PackageStorage::getInstance().storeGameListPackage(paquet);
		PackageStorage::getInstance().deleteReceivedPackage();
	};
	tab[3] = [this](Paquet *paquet UNUSED) {};
	tab[4] = [this](Paquet *paquet UNUSED) {};
	tab[5] = [this](Paquet *paquet UNUSED) {};
	tab[6] = [this](Paquet *paquet UNUSED) {
		PackageStorage::getInstance().storePlayerListPackage(paquet);
		PackageStorage::getInstance().deletePlayerListPackage();
	};
	tab[7] = [this](Paquet *paquet) {
		PackageStorage::getInstance().storePlayersPackage(paquet);
		PackageStorage::getInstance().deletePlayerListPackage();
	};
	tab[8] = [this](Paquet *paquet) {
		PackageStorage::getInstance().storeShotsPackage(paquet);
		PackageStorage::getInstance().deletePlayerListPackage();
	};
	tab[9] = [this](Paquet *paquet) {
		PackageStorage::getInstance().storeObstaclesPackage(paquet);
		PackageStorage::getInstance().deletePlayerListPackage();
	};
	tab[10] = [this](Paquet *paquet UNUSED) {};
	tab[11] = [this](Paquet *paquet UNUSED) {};
	tab[12] = [this](Paquet *paquet UNUSED) {};

	Callback_t fptr = [this](void *arg) {this->sortPaquet(); return nullptr; };
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
    if (PackageStorage::getInstance().isThereReceivedPackage()) {
      const Paquet *paquet = PackageStorage::getInstance().getReceivedPackage();
      tab[paquet->getData()[0]](const_cast<Paquet*>(paquet));
    }
  }
}

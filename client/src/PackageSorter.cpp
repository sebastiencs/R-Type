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
  storage = new PackageStorage();
}

PackageSorter::PackageSorter(PackageStorage * storage) : storage(storage)
{
}

PackageSorter::~PackageSorter()
{
}

void PackageSorter::sortPaquet()
{
  std::function<void(Paquet *)> tab[13];
  tab[0] = [this](Paquet *paquet UNUSED) {};
  tab[1] = [this](Paquet *paquet UNUSED) {};
  tab[2] = [this](Paquet *paquet) {
    storage->storeGameListPackage(paquet);
    storage->deleteReceivedPackage();
  };
  tab[3] = [this](Paquet *paquet UNUSED) {};
  tab[4] = [this](Paquet *paquet UNUSED) {};
  tab[5] = [this](Paquet *paquet UNUSED) {};
  tab[6] = [this](Paquet *paquet UNUSED) {
    storage->storePlayerListPackage(paquet);
    storage->deletePlayerListPackage();
  };
  tab[7] = [this](Paquet *paquet) {
    storage->storePlayersPackage(paquet);
    storage->deletePlayerListPackage();
  };
  tab[8] = [this](Paquet *paquet) {
    storage->storeShotsPackage(paquet);
    storage->deletePlayerListPackage();
  };
  tab[9] = [this](Paquet *paquet) {
    storage->storeObstaclesPackage(paquet);
    storage->deletePlayerListPackage();
  };
  tab[10] = [this](Paquet *paquet UNUSED) {};
  tab[11] = [this](Paquet *paquet UNUSED) {};
  tab[12] = [this](Paquet *paquet UNUSED) {};

  while (1)
  {
    if (storage->isThereReceivedPackage()) {
      const Paquet *paquet = storage->getReceivedPackage();
      tab[paquet->getData()[0]](const_cast<Paquet*>(paquet));
    }
  }
}

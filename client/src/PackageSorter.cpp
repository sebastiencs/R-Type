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
  std::function<void(Paquet *)> tab[4];
  tab[0] = [this](Paquet *paquet) {storage->storeEnemiesPackage(paquet); };
  tab[1] = [this](Paquet *paquet) {storage->storeObstaclesPackage(paquet); };
  tab[2] = [this](Paquet *paquet) {storage->storePlayersPackage(paquet); };
  tab[3] = [this](Paquet *paquet) {storage->storeShotsPackage(paquet); };

  while (1)
  {
    //if (anyPaquet) {
      const Paquet *paquet = storage->getReceivedPackage();
      tab[paquet->getData()[0]](const_cast<Paquet*>(paquet));
      delete(paquet);
    //}
  }
}

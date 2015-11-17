//
// PackageSorter.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 02:08:19 2015 chapui_s
// Last update Sun Nov 15 02:08:19 2015 chapui_s
//

#include "..\includes\PackageSorter.hh"

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

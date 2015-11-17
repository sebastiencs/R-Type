//
// PackageSorter.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 02:08:19 2015 chapui_s
// Last update Sun Nov 15 02:08:19 2015 chapui_s
//

#ifndef PACKAGE_SORTER_HH
# define PACKAGE_SORTER_HH

# include <iostream>
# include <list>
# include <map>
# include <functional>
# include "PackageStorage.hh"

class PackageSorter {
public:
  PackageSorter();
  PackageSorter(PackageStorage *storage);
  virtual ~PackageSorter();
  void sortPaquet();

private:
  PackageStorage *storage;
};

#endif /* !PACKAGE_SORTER_HH */
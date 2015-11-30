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
# include <functional>
# include "PackageStorage.hh"
# include "Thread.hh"

class PackageSorter {
public:
	PackageSorter();
	virtual ~PackageSorter();
	std::function<void(Paquet *)> tab[13];
	void sortPaquet();

private:
	Thread *thread;
};

#endif /* !PACKAGE_SORTER_HH */
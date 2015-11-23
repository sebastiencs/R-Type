#ifndef PACKAGER_HH
#define PACKAGER_HH

class Packager {
public:
	Packager();
	virtual ~Packager();

	void createMovementPackage();
	void createShotPackage();
};

#endif PACKAGER_HH
#ifndef PACKAGETRANSLATOR_HH
#define PACKAGETRANSLATOR_HH

#include <iostream>
#include "PackageStorage.hh"
#include "Buffer.hh"

class PackageTranslator {
private:
  PackageStorage* storage;

public:
  PackageTranslator();
  virtual ~PackageTranslator();

  Paquet* BufferToPaquet(const Buffer& buff);
  Buffer* PaquetToBuffer(const Paquet& paquet);
};

#endif /* !PACKAGETRANSLATOR_HH */

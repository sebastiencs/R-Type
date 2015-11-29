#ifndef PACKAGETRANSLATOR_HH
#define PACKAGETRANSLATOR_HH

#include <iostream>
#include "PackageStorage.hh"
#include "Buffer.hh"

class PackageTranslator {
public:
  PackageTranslator();
  virtual ~PackageTranslator();

  void BufferToPaquet(const Buffer& buff);
  void PaquetToBuffer(const Paquet& paquet);
  Paquet* TranslatePaquet(const Buffer& buff);
  Buffer* TranslateBuffer(const Paquet& paquet);
};

#endif /* !PACKAGETRANSLATOR_HH */

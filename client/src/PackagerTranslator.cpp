#include <functional>
#include <PackagerTranslator.hh>
#include <Paquets.hh>

PackageTranslator::PackageTranslator()
{
  storage = new PackageStorage();
}

PackageTranslator::PackageTranslator(PackageStorage * storage) : storage(storage)
{
}

PackageTranslator::~PackageTranslator()
{
}

Paquet * PackageTranslator::BufferToPaquet(const Buffer& buff)
{
  Paquet*	paquet = new Paquet(buff.get(), buff.size());

  return paquet;
}

Buffer * PackageTranslator::PaquetToBuffer(const Paquet& paquet)
{
  Buffer *buf = new Buffer();
  
  buf->set(paquet.getData(), paquet.getSize());
  return buf;
}


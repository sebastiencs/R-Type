#include <functional>
#include <PackagerTranslator.hh>
#include <Paquets.hh>

PackageTranslator::PackageTranslator()
{
}

PackageTranslator::~PackageTranslator()
{
}

void PackageTranslator::BufferToPaquet(const Buffer& buff)
{
	Paquet*	paquet = new Paquet(buff.get(), buff.size());
	//PackageStorage::getInstance().storeReceivedPackage(paquet);
}

void PackageTranslator::PaquetToBuffer(const Paquet& paquet)
{
  Buffer *buf = new Buffer();
  
  buf->set(paquet.getData(), paquet.getSize());
//  PackageStorage::getInstance().storeToSendPackage(buf);
}

Paquet* PackageTranslator::TranslatePaquet(const Buffer& buff)
{
	Paquet*	paquet = new Paquet(buff.get(), buff.size());
	return paquet;
}

Buffer* PackageTranslator::TranslateBuffer(const Paquet& paquet)
{
	Buffer *buf = new Buffer();

	buf->set(paquet.getData(), paquet.getSize());
	return buf;
}

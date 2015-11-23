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
  std::function<Paquet *(const Buffer&)> tab[13];
  tab[0] = [this](const Buffer& buff) {return (new PaquetFirst(buff)); };
  tab[1] = [this](const Buffer& buff) {return (new PaquetRequestParties(buff)); };
  tab[2] = [this](const Buffer& buff) {return (new PaquetListPlayers(buff)); };
  tab[3] = [this](const Buffer& buff) {return (new PaquetJoinParty(buff)); };
  tab[4] = [this](const Buffer& buff) {return (new PaquetCreateParty(buff)); };
  tab[5] = [this](const Buffer& buff) {return (new PaquetRequestPlayers(buff)); };
  tab[6] = [this](const Buffer& buff) {return (new PaquetListPlayers(buff)); };
  tab[7] = [this](const Buffer& buff) {return (new PaquetPlayerCoord(buff)); };
  tab[8] = [this](const Buffer& buff) {return (new PaquetPlayerShot(buff)); };
  tab[9] = [this](const Buffer& buff) {return (new PaquetObstacle(buff)); };
  tab[10] = [this](const Buffer& buff) {return (new PaquetReady(buff)); };
  tab[11] = [this](const Buffer& buff) {return (new PaquetLaunch(buff)); };
  tab[12] = [this](const Buffer& buff) {return (new PaquetLeave(buff)); };

  size_t	ptr = 0;
  uint8_t id;

  writeData<char>(ptr, reinterpret_cast<const char *>(buff.get()), buff.size());
  id = readData<uint8_t>(ptr);
  return tab[id](buff);
}

Buffer * PackageTranslator::PaquetToBuffer(const Paquet& paquet)
{
  Buffer *buf = new Buffer();
  
  buf->set(paquet.getData(), paquet.getSize());
  return buf;
}


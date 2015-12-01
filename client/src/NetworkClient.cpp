#include <NetworkClient.hh>

NetworkClient::NetworkClient(const std::string& ip, const uint16_t port)
  : _socketUDP(new SocketUDP(SocketUDP::CLIENT)),
    _socketTCP(new SocketTCP(SocketTCP::CLIENT))
{
	PaquetFirst *paquet = new PaquetFirst();
	paquet->setLevel(5);
	paquet->setName("Alex");
	paquet->setVersion(1);
	paquet->createPaquet();
	PackageStorage::getInstance().storeToSendPackage(paquet);

	if ((_socketTCP->connect(ip, port)) == -1)
		_isConnect = false;
	else
		_isConnect = true;

	Callback_t fptrWrite = [this] (void *) {runWrite(); return nullptr; };
	Callback_t fptrRead = [this] (void *) {runRead(); return nullptr; };
	inGame = false;
	threadWrite = new Thread(fptrWrite, nullptr);
	threadRead = new Thread(fptrRead, nullptr);
	if (!_isConnect)
	{
		threadRead->close();
		threadWrite->close();
	}
}

NetworkClient::~NetworkClient()
{
	if (_isConnect) {
		threadRead->close();
		threadWrite->close();
	}
	delete threadWrite;
	delete threadRead;
	delete _socketTCP;
	delete _socketUDP;
	DEBUG_MSG("NetworkClient deleted");
}

int NetworkClient::runWrite()
{
	Pollfd	fds(2);

	fds[0].fd = _socketTCP->socket();
	fds[0].events = POLLOUT;
	fds[1].fd = _socketUDP->socket();
	fds[1].events = POLLOUT;

	while (1)
	{
		PackageStorage::getInstance().waitForPackage();
		if (IOEvent::poll(fds, 0) > 0)
		{
			for (auto fd : fds)
			{
				if (fd.revents & POLLOUT)
				{
					if (fd.fd == _socketUDP->socket())
					{
						const Paquet *paquet = PackageStorage::getInstance().getToSendPackage();
						if (paquet != nullptr) {
							PackageStorage::getInstance().getAnswersPackage();
							this->writeUDP(*paquet, _socketUDP->getAddr());
							PackageStorage::getInstance().deleteToSendPackage();
						}
						break;
					}
					else if (fd.fd == _socketTCP->socket())
					{
						const Paquet *paquet = PackageStorage::getInstance().getToSendPackage();
						if (paquet != nullptr) {
							PackageStorage::getInstance().getAnswersPackage();
							this->writeTCP(*paquet);
							PackageStorage::getInstance().deleteToSendPackage();
						}
						break;
					}
				}
			}
		}
	}
	return (0);

}

int NetworkClient::runRead()
{
	Pollfd	fds(2);

	fds[0].fd = _socketTCP->socket();
	fds[0].events = POLLIN;
	fds[1].fd = _socketUDP->socket();
	fds[1].events = POLLIN;

	while (1)
	{
		if (IOEvent::poll(fds, 0) > 0)
		{
			for (auto fd : fds)
			{
				if (fd.revents & POLLIN)
				{
					if (fd.fd == _socketUDP->socket())
					{
						Buffer buff;
						this->_socketUDP->read(buff);
						DEBUG_MSG(buff);
						PackageStorage::getInstance().storeReceivedPackage(PackageTranslator::TranslatePaquet(buff));
						break;
					}
					else if (fd.fd == _socketTCP->socket())
					{
						Buffer buff;
						this->_socketTCP->read(buff);
						DEBUG_MSG(buff);
						PackageStorage::getInstance().storeReceivedPackage(PackageTranslator::TranslatePaquet(buff));
						break;
					}

				}
			}
		}
	}
	return (0);
}

int NetworkClient::stop()
{
  return 0;
}

int NetworkClient::handleFirst(PaquetFirst first)
{
  _socketTCP->write(first);
  DEBUG_MSG(first);
  return 0;
}

void NetworkClient::setInGame(bool _inGame)
{
	inGame = _inGame;
}

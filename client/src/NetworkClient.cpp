#include <NetworkClient.hh>
#include "ListPlayers.hh"
#include "PaquetTCP.hh"
#include "Tools.hh"
#include "PackagerTranslator.hh"

NetworkClient::NetworkClient(const std::string& ip, const uint16_t port)
	: _socketUDP(new SocketUDP(SocketUDP::CLIENT)),
	_socketTCP(new PaquetTCP(SocketTCP::CLIENT))
{
	PaquetFirst *paquet = new PaquetFirst();

	// Creation du player
	ListPlayers &list = ListPlayers::getInstance();
	std::string name = Tools::getUser();
	Player *player = new Player(name, 0, 0);
	list.addPlayer(player);
	//!Creation

	paquet->setLevel(player->getLevel());
	paquet->setName(player->getName());
	paquet->setVersion(1);
	paquet->createPaquet();
	PackageStorage::getInstance().storeToSendTCPPackage(paquet);
	
	_ip = ip;
	_port = port;

	if ((_socketTCP->connect(ip, port)) == -1 || (_socketUDP->connect(ip, port)) == -1) {
		_isConnect = false;
		_socketTCP.reset(nullptr);
		_socketUDP.reset(nullptr);
		return;
	}
	_isConnect = true;

	inGame = false;
	Callback_t fptrWrite = [this](void *) {runWrite(); return nullptr; };
	threadWrite = new Thread(fptrWrite, this);
	Callback_t fptrRead = [this](void *) {runRead(); return nullptr; };
	threadRead = new Thread(fptrRead, this);
}

NetworkClient::~NetworkClient()
{
	if (_isConnect) {
		threadRead->close();
		DEBUG_MSG("ThreadRead close");
		threadWrite->close();
		DEBUG_MSG("ThreadWrite close");
		delete threadWrite;
		DEBUG_MSG("ThreadWrite deleted");
		delete threadRead;
		DEBUG_MSG("ThreadRead deleted");
	}
	_socketTCP.reset(nullptr);
	DEBUG_MSG("SocketTCP deleted");
	_socketUDP.reset(nullptr);
	DEBUG_MSG("SocketUDP deleted");
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
		if (IOEvent::poll(fds, IOEvent::POLL_WAIT) > 0)
		{
			for (auto &fd : fds)
			{
				if (fd.revents & POLLOUT)
				{
					if (fd.fd == _socketUDP->socket())
					{
						const Paquet *paquet = PackageStorage::getInstance().getToSendUDPPackage();
						if (paquet != nullptr) {
							DEBUG_MSG("Send paquet");
							this->writeUDP(*paquet);
							PackageStorage::getInstance().deleteToSendUDPPackage();
							break;
						}
					}
					else if (fd.fd == _socketTCP->socket())
					{
						const Paquet *paquet = PackageStorage::getInstance().getToSendTCPPackage();
						if (paquet != nullptr) {
							DEBUG_MSG("Send paquet");
							this->writeTCP(*paquet);
							PackageStorage::getInstance().deleteToSendTCPPackage();
							break;
						}
					}
				}
			}
		}
	}
	return (0);
}

int NetworkClient::runRead()
{
	Buffer buffer;
	Pollfd	fds(2);

	fds[0].fd = _socketTCP->socket();
	fds[0].events = POLLIN;
	fds[1].fd = _socketUDP->socket();
	fds[1].events = POLLIN;

	while (1)
	{
		if (IOEvent::poll(fds, IOEvent::POLL_WAIT) > 0)
		{
			for (auto &fd : fds)
			{
				if (fd.revents & POLLIN)
				{
					if (fd.fd == _socketUDP->socket())
					{
						this->_socketUDP->read(buffer);
						PackageStorage::getInstance().storeReceivedPackage(PackageTranslator::TranslatePaquet(buffer));
						break;
					}
					else if (fd.fd == _socketTCP->socket())
					{
						ssize_t n;

						try {
							n = this->_socketTCP->read(buffer);
						}
						catch (Disconnected &) {

							DEBUG_MSG("Disconnected");

							_isConnect = false;
							inGame = false;
							threadWrite->close();
							_socketTCP.reset(nullptr);
							_socketUDP.reset(nullptr);
							threadRead->close();
							return (0);

						}

						if (n > 0) {
							DEBUG_MSG(buffer);
							PackageStorage::getInstance().storeReceivedPackage(PackageTranslator::TranslatePaquet(buffer));
						}
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

int NetworkClient::reconnect()
{
	_socketTCP.reset(new SocketTCP(SocketTCP::CLIENT));
	_socketUDP.reset(new SocketUDP(SocketUDP::CLIENT));

	if ((_socketTCP->connect(_ip, _port)) == -1)
	{
		_isConnect = false;
		return (-1);
	}
	_isConnect = true;
	inGame = false;
	Callback_t fptrWrite = [this](void *) {runWrite(); return nullptr; };
	threadWrite = new Thread(fptrWrite, this);
	Callback_t fptrRead = [this](void *) {runRead(); return nullptr; };
	threadRead = new Thread(fptrRead, this);
	return (1);
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

bool NetworkClient::getIsConnect()
{
	return _isConnect;
}

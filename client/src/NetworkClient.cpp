#include <NetworkClient.hh>
#include "ListPlayers.hh"
#include "PaquetTCP.hh"
#include "Tools.hh"

NetworkClient::NetworkClient(const std::string& ip, const uint16_t port)
  : _socketUDP(std::make_unique<SocketUDP>(SocketUDP::CLIENT)),
    _socketTCP(std::make_unique<PaquetTCP>(SocketTCP::CLIENT))
{
	auto &&paquet = std::make_shared<PaquetFirst>();

	// Creation du player
	ListPlayers &list = ListPlayers::getInstance();
	std::string name = Tools::getUser();
	Player_SharedPtr player = std::make_shared<Player>(name, 0, 0);
	list.addPlayer(std::move(player));
	list.setId(0);
	//!Creation

	condR = 1;
	condW = 1;

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
	Callback_t fptrWrite = [this](void *c) {runWrite(reinterpret_cast<int *>(c)); return nullptr; };
	threadWrite = std::make_shared<Thread>(fptrWrite, &condW);
	Callback_t fptrRead = [this](void *c) {runRead(reinterpret_cast<int *>(c)); return nullptr; };
	threadRead = std::make_shared<Thread>(fptrRead, &condR);
}

NetworkClient::~NetworkClient()
{
  	condR = 0;
  	condW = 0;
	if (_isConnect) {
		threadWrite->join();
		DEBUG_MSG("ThreadWrite deleted");
		threadRead->join();
		DEBUG_MSG("ThreadRead deleted");
	}
	_socketTCP.reset(nullptr);
	DEBUG_MSG("SocketTCP deleted");
	_socketUDP.reset(nullptr);
	DEBUG_MSG("SocketUDP deleted");
}

int NetworkClient::runWrite(int *cond)
{
	PackageStorage &PS = PackageStorage::getInstance();
	Pollfd	fds(2);

	fds[0].fd = _socketTCP->socket();
	fds[0].events = POLLOUT;
	fds[1].fd = _socketUDP->socket();
	fds[1].events = POLLOUT;

	while (*cond)
	{
		if (PS.waitForPackage() == false) {
			continue ;
		}
		if (IOEvent::poll(fds, IOEvent::POLL_WAIT) > 0)
		{
			for (auto &fd : fds)
			{
				if (fd.revents & POLLOUT)
				{
					if (fd.fd == _socketUDP->socket())
					{
						auto &paquet = PS.getToSendUDPPackage();
						if (paquet != nullptr) {
//							DEBUG_MSG("Send paquet");
							this->writeUDP(*paquet);
							PS.deleteToSendUDPPackage();
							break;
						}
					}
					else if (fd.fd == _socketTCP->socket())
					{
						auto &paquet = PS.getToSendTCPPackage();
						if (paquet != nullptr) {
//							DEBUG_MSG("Send paquet");
							this->writeTCP(*paquet);
							PS.deleteToSendTCPPackage();
							break;
						}
					}
				}
			}
		}
	}
	return (0);
}

int NetworkClient::runRead(int *cond)
{
	PackageStorage &PS = PackageStorage::getInstance();
	Buffer buffer;
	Pollfd	fds(2);

	fds[0].fd = _socketTCP->socket();
	fds[0].events = POLLIN;
	fds[1].fd = _socketUDP->socket();
	fds[1].events = POLLIN;

	while (*cond)
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
						PS.storeReceivedPackage(std::make_shared<Paquet>(buffer));
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
							condW = 0;
							condR = 0;
							// threadWrite->close();
							_socketTCP.reset(nullptr);
							_socketUDP.reset(nullptr);
							// threadRead->close();
							return (0);

						}

						if (n > 0) {
							DEBUG_MSG(buffer);
							PS.storeReceivedPackage(std::make_shared<Paquet>(buffer));
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
	_socketTCP = std::make_unique<SocketTCP>(SocketTCP::CLIENT);
	_socketUDP = std::make_unique<SocketUDP>(SocketUDP::CLIENT);

	if ((_socketTCP->connect(_ip, _port)) == -1)
	{
		_isConnect = false;
		return (-1);
	}
	_isConnect = true;
	inGame = false;
	Callback_t fptrWrite = [this](void *c) {runWrite(reinterpret_cast<int *>(c)); return nullptr; };
	threadWrite = std::make_shared<Thread>(fptrWrite, this);
	Callback_t fptrRead = [this](void *c) {runRead(reinterpret_cast<int *>(c)); return nullptr; };
	threadRead = std::make_shared<Thread>(fptrRead, this);
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

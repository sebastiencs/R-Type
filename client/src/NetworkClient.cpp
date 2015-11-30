#include <NetworkClient.hh>

NetworkClient::NetworkClient(const std::string& ip, const uint16_t port)
  : _socketUDP(new SocketUDP(SocketUDP::CLIENT)),
    _socketTCP(new SocketTCP(SocketTCP::CLIENT))
{
  _socketTCP->connect(ip, port);
}

NetworkClient::~NetworkClient()
{
  DEBUG_MSG("NetworkClient deleted");
}

int NetworkClient::run()
{
	Pollfd	fds(2);

	fds[0].fd = _socketTCP->socket();
	fds[0].events = POLLIN | POLLOUT;
	fds[1].fd = _socketUDP->socket();
	fds[1].events = POLLIN | POLLOUT;

	while (1)
	{
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
							this->writeUDP(*PackageTranslator::TranslateBuffer(*paquet), _socketUDP->getAddr());
						}
						break;
					}
					else if (fd.fd == _socketTCP->socket())
					{
//						handleNewTCP(fds);
						break;
					}
				}
				else if (fd.revents && POLLIN)
				{
					if (fd.fd == _socketUDP->socket())
					{
						if (PackageStorage::getInstance().isThereReceivedPackage())
							PackageStorage::getInstance().getAnswersPackage();
						break;
					}
					else if (fd.fd == _socketTCP->socket())
					{
//						handleNewTCP(fds);
						break;
					}

				}
			}
		}
		else
			return (-1);
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

bool NetworkClient::writeUDP(const Buffer& buf, const Addr& addr)
{
  if ((_socketUDP->write(buf, addr)) == 0)
    return true;
  return false;
}

bool NetworkClient::writeTCP(const Buffer& buf)
{
  if ((_socketTCP->write(buf)) == 0)
    return true;
  return false;
}

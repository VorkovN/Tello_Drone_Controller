#include "TelloDriver.h"


TelloDriver::TelloDriver():
		_commandSockfd(socket(AF_INET, SOCK_DGRAM, 0)),
		_stateSockfd(socket(AF_INET, SOCK_DGRAM, 0))
{
	if (!bindSockets())
	{
		std::cout << "Binding error";
		exit(1);
	}
	std::cout << "Tello driver has been created" << std::endl;
}

TelloDriver::~TelloDriver()
{
	close(_commandSockfd);
	close(_stateSockfd);
}

///////////////////<<ПРИВЯЗКА СОКЕТОВ>>////////////////////////

std::pair<bool, std::string> TelloDriver::bindSocketToPort(const int sockfd, const int port)
{
	//по инструкции надо почистить
	memset(&_stSockAddr, 0, sizeof(_stSockAddr));

	//стандартное привязывание адреса
	_stSockAddr.sin_port = htons(port);
	_stSockAddr.sin_addr.s_addr = INADDR_ANY;
	_stSockAddr.sin_family = AF_INET;
	int result = bind(sockfd, (struct sockaddr*)&_stSockAddr, sizeof(_stSockAddr));

	if (result == -1)
		return { false, "error binding" };

	return { true, "" };
}

std::pair<bool, std::string> TelloDriver::findSocketAddr(const char* const ip, const char* const port, sockaddr* const addr)
{
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_DGRAM;
	int result = getaddrinfo(ip, port, &_hints, &_resultList);

	if (result != 0)
		return { false, "getaddrinfo: " + std::to_string(result) };

	memcpy(addr, _resultList->ai_addr, _resultList->ai_addrlen);
	freeaddrinfo(_resultList);

	return { true, "" };
}

bool TelloDriver::bindSockets()
{
	std::pair<bool, std::basic_string<char>> result;
	// UDP клиент для command
	result = bindSocketToPort(_commandSockfd, constants::LOCAL_CLIENT_COMMAND_PORT);
	if (!result.first)
	{
		std::cerr << result.second;
		return false;
	}

	//заполняем _telloServerCommandAddr
	result = findSocketAddr(constants::TELLO_SERVER_IP, constants::TELLO_SERVER_COMMAND_PORT, &_telloServerCommandAddr);
	if (!result.first)
	{
		std::cerr << result.second;
		return false;
	}

	// UDP сервер для state
	result = bindSocketToPort(_stateSockfd, constants::LOCAL_SERVER_STATE_PORT);
	if (!result.first)
	{
		std::cerr << result.second;
		return false;
	}

	return true;
}

///////////////////<<ОТПРАВКА ПАКЕТА>>////////////////////////
bool TelloDriver::sendCommand(const std::string& command)
{
	const std::vector<unsigned char> message(command.begin(), command.end());
	const socklen_t addr_len = sizeof(_telloServerCommandAddr);

	ssize_t result = sendto(_commandSockfd, message.data(), message.size(), 0, &_telloServerCommandAddr, addr_len);

	if (result == -1)
		return false;

	return true;
}

///////////////////<<ПОЛУЧЕНИЕ ПАКЕТА>>////////////////////////
std::pair<bool, std::string> TelloDriver::receiveResponse()
{
	const int buf_size = 32;
	std::vector<unsigned char> buffer(buf_size, '\0');
	socklen_t addr_len = sizeof(_telloServerCommandAddr);

	ssize_t result = recvfrom(_commandSockfd, buffer.data(), buf_size, MSG_DONTWAIT, &_telloServerCommandAddr, &addr_len);

	if (result < 1)
		return std::make_pair(false, "");

	std::string response(buffer.begin(), buffer.begin() + result);

	return std::make_pair(true, response);
}

///////////////////<<ПОЛУЧЕНИЕ ПАКЕТА СТАТУСА>>////////////////////////
std::pair<bool, std::string> TelloDriver::receiveStatus() const
{
	const int buf_size = 1024;
	std::vector<unsigned char> buffer(buf_size, '\0');
	ssize_t result = recvfrom(_stateSockfd, buffer.data(), buf_size, MSG_DONTWAIT, nullptr, nullptr);

	if (result < 1)
		return std::make_pair(false, "No Result");

	std::string response(buffer.begin(), buffer.begin() + result);

	return std::make_pair(true, response);
}




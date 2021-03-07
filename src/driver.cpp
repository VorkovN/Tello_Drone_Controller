#include "driver.h"


Tello::Tello()
{
	command_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	state_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (!bindSockets())
	{
		std::cout << "Binding error";
		exit(1);
	}
	findTello();//отправка инициализирующей команды
}

Tello::~Tello()
{
	close(command_sockfd);
	close(state_sockfd);
}

//привязываем сокет к порту
std::pair<bool, std::string> Tello::bindSocketToPort(const int sockfd, const int port)
{
	//по инструкции надо почистить
	memset(&stSockAddr, 0, sizeof(stSockAddr));

	//стандартное привязывание адреса
	stSockAddr.sin_port = htons(port);
	stSockAddr.sin_addr.s_addr = INADDR_ANY;
	stSockAddr.sin_family = AF_INET;
	int result = bind(sockfd, (struct sockaddr*)&stSockAddr, sizeof(stSockAddr));

	if (result == -1)
		return { false, "error binding" };

	return { true, "" };
}


std::pair<bool, std::string>
Tello::findSocketAddr(const char* const ip, const char* const port, sockaddr_storage* const addr)
{
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	int result = getaddrinfo(ip, port, &hints, &result_list);

	if (result != 0)
		return { false, "getaddrinfo: " + std::to_string(result) };

	memcpy(addr, result_list->ai_addr, result_list->ai_addrlen);
	freeaddrinfo(result_list);

	return { true, "" };
}


bool Tello::sendCommand(const std::string& command)
{
	const std::vector<unsigned char> message{ command.begin(), command.end() };

	const socklen_t addr_len = sizeof(tello_server_command_addr);
	int result = sendto(command_sockfd, message.data(), message.size(), 0, reinterpret_cast<sockaddr*>(&tello_server_command_addr), addr_len);

	if (result == -1)
		return false;

	return true;
}

std::string Tello::receiveResponse()
{
	const int buf_size = 32;
	std::vector<unsigned char> buffer(buf_size, '\0');
	socklen_t addr_len = sizeof(tello_server_command_addr);
	buffer.resize(buf_size, '\0');

	int result = recvfrom(command_sockfd, buffer.data(), buf_size, MSG_DONTWAIT, reinterpret_cast<sockaddr*>(&tello_server_command_addr), &addr_len);

	if (result < 1)
		return "";

	std::string response = { buffer.begin(), buffer.begin() + result };

	return response;
}

void Tello::findTello()
{
	std::cout << "Finding Tello ..." << std::endl;
	sendCommand("command");
	sleep(1);

	while (receiveResponse().empty())
	{
		sendCommand("command");
		sleep(1);
	}
}


bool Tello::bindSockets()
{
	// UDP клиент для command
	auto result = bindSocketToPort(command_sockfd, LOCAL_CLIENT_COMMAND_PORT);
	if (!result.first)
	{
		std::cerr << result.second;
		return false;
	}

	result = findSocketAddr(TELLO_SERVER_IP, TELLO_SERVER_COMMAND_PORT, &tello_server_command_addr);
	if (!result.first)
	{
		std::cerr << result.second;
		return false;
	}

	// UDP сервер для state
	result = bindSocketToPort(state_sockfd, LOCAL_SERVER_STATE_PORT);
	if (!result.first)
	{
		std::cerr << result.second;
		return false;
	}

	return true;
}

std::string Tello::receiveStatus()
{
	const int buf_size = 1024;
	sockaddr_storage addr{};
	socklen_t addr_len = sizeof(addr);
	std::vector<unsigned char> buffer(buf_size, '\0');
	int result = recvfrom(state_sockfd, buffer.data(), buf_size, MSG_DONTWAIT, reinterpret_cast<sockaddr*>(&addr), &addr_len);

	if (result < 1)
		return "No status";

	return {buffer.begin(), buffer.begin() + result};
}




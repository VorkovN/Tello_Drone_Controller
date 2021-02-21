// https://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D0%BA%D0%B5%D1%82%D1%8B_%D0%91%D0%B5%D1%80%D0%BA%D0%BB%D0%B8

#include "tello_driver.h"


Tello::Tello()
{
	command_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	state_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
}

//привязываем сокет к порту
std::pair<bool, std::string> Tello::BindSocketToPort(const int sockfd, const int port)
{
	//по инструкции надо почистить
	memset(&stSockAddr, 0, sizeof (stSockAddr));

	//стандартное привязывание адреса
	stSockAddr.sin_port = htons(port);
	stSockAddr.sin_addr.s_addr = INADDR_ANY;
	stSockAddr.sin_family = AF_INET;
	int result = bind(sockfd, (struct sockaddr*) &stSockAddr,sizeof(stSockAddr));

	if (result == -1)
		return {false, "error binding"};

	return {true, ""};
}

//
//std::pair<bool, std::string> FindSocketAddr(const char* const ip,
//		const char* const port,
//		sockaddr_storage* const addr)
//{
//	addrinfo* result_list{nullptr};
//	addrinfo hints{};
//	hints.ai_family = AF_INET;
//	hints.ai_socktype = SOCK_DGRAM;
//	int result = getaddrinfo(ip, port, &hints, &result_list);
//
//	if (result != 0)
//	{
//		std::stringstream ss;
//		ss << "getaddrinfo: " << result;
//		ss << " (" << gai_strerror(result) << ") ";
//		return {false, ss.str()};
//	}
//
//	memcpy(addr, result_list->ai_addr, result_list->ai_addrlen);
//	freeaddrinfo(result_list);
//
//	return {true, ""};
//}



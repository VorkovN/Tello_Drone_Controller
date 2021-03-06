#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <memory.h>
#include <unistd.h>
#include <vector>
//#include <sys/types.h>

#include <optional>// or we can take it from boost library
//#include <vector>
//#include <string>

const char* const TELLO_SERVER_IP{"192.168.10.1"};// sudo arp-scan --interface=wlp1s0 --localnet
const char* const TELLO_SERVER_COMMAND_PORT{"8889"};
const int LOCAL_CLIENT_COMMAND_PORT{9000};
const int LOCAL_SERVER_STATE_PORT{8890};


class Tello
{
 public:
	Tello();
	~Tello();


	Tello(const Tello&) = delete;
	Tello(const Tello&&) = delete;
	Tello& operator=(const Tello&) = delete;
	Tello& operator=(const Tello&&) = delete;

 public:
	std::pair<bool, std::string>  bindSocketToPort(const int sockfd, const int port);
	std::pair<bool, std::string> findSocketAddr(const char* const ip, const char* const port, sockaddr_storage* const addr);
	bool sendCommand(const std::string& command);
	std::string receiveResponse();
	void findTello();
	bool bindSockets();
	std::string receiveStatus();


 private:
	int command_sockfd{0};
	int state_sockfd{0};
	addrinfo* result_list{nullptr};
	addrinfo hints{};
	sockaddr_in stSockAddr{};
	sockaddr_storage tello_server_command_addr{};
};
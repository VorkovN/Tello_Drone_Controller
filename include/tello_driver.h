#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <memory.h>
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
	BindSocketToPort(const int sockfd, const int port);

 private:
	int command_sockfd{0};
	int state_sockfd{0};
	sockaddr_in stSockAddr;
	int m_local_client_command_port{LOCAL_CLIENT_COMMAND_PORT};
	sockaddr_storage m_tello_server_command_addr{};
};
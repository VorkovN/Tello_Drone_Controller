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
#include "StatusParams.h"

const char* const TELLO_SERVER_IP{"192.168.10.1"};// sudo arp-scan --interface=wlp1s0 --localnet
const char* const TELLO_SERVER_COMMAND_PORT = "8889";
const int LOCAL_CLIENT_COMMAND_PORT = 9000;
const int LOCAL_SERVER_STATE_PORT = 8890;


class TelloDriver
{
 public:
	TelloDriver();
	~TelloDriver();


	TelloDriver(const TelloDriver&) = default;
	TelloDriver(const TelloDriver&&) = delete;
	TelloDriver& operator=(const TelloDriver&) = delete;
	TelloDriver& operator=(const TelloDriver&&) = delete;

 public:
	std::pair<bool, std::string> bindSocketToPort(const int sockfd, const int port);
	std::pair<bool, std::string> findSocketAddr(const char* const ip, const char* const port, sockaddr_storage* const addr);
	std::pair<bool, std::string> receiveResponse();
	std::pair<bool, std::string> receiveStatus() const;
	bool sendCommand(const std::string& command);
	void findTello();
	bool bindSockets();


 private:
	int _commandSockfd = 0;
	int _stateSockfd = 0;
	addrinfo* _resultList = nullptr;
	addrinfo _hints{};
	sockaddr_in _stSockAddr{};
	sockaddr _telloServerCommandAddr{};

	StatusParams _statusParams;
};
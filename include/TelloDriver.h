#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <memory.h>
#include <unistd.h>
#include <vector>

#include "StatusParams.h"
#include "Constants.h"



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
	std::pair<bool, std::string> findSocketAddr(const char* const ip, const char* const port, sockaddr* const addr);
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
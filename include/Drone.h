#pragma once
#include <thread>

#include "TelloDriver.h"
#include "StatusController.h"
#include "VideoController.h"
#include "CommandController.h"

class Drone
{
 public:
	Drone();
	~Drone();

	bool executeCommand(const std::string& command);
	void startVideo();
	void stopVideo();

 private:
	void saveStatus();
	void receiveStatus();
	void printStatus() const;

 private:
	TelloDriver _telloDriver;
	CommandController _commandController;
	VideoController _videoController;
	StatusController _statusController;

	std::thread _videoThread;
	std::thread _statusThread;

	StatusParams _statusParams;
};

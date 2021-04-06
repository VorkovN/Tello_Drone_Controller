#pragma once
#include <thread>

#include "TelloDriver.h"
#include "StatusController.h"
#include "VideoController.h"

class Drone
{
 public:
	Drone();
	~Drone();

	void startVideo();
	void stopVideo();

 private:
	void saveStatus();
	void receiveStatus();
	void printStatus() const;

 private:
	TelloDriver _tello_driver;
	VideoController _videoController;
	StatusController _statusController;

	std::thread _videoThread;
	std::thread _statusThread;

	StatusParams _statusParams;
};

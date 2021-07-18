#pragma once
#include <QString>


#include "TelloDriver.h"
#include "StatusController.h"
#include "VideoController.h"
#include "CommandController.h"
#include "Constants.h"

class Drone
{
 public:
	Drone();
	~Drone();

	bool executeCommand(std::string command);

	cv::Mat returnVideoFrame();
	QString returnStatus();

 private:
	void checkStatus();

 private:
	TelloDriver _telloDriver;
	CommandController _commandController;
    StatusController _statusController;
	VideoController _videoController;

	StatusParams _statusParams;
};

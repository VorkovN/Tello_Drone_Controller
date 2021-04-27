#pragma once
#include <thread>

#include "TelloDriver.h"
#include "StatusController.h"
#include "VideoController.h"
#include "CommandController.h"
#include "tellowindow.h"
#include "./ui_tellowindow.h"
#include <QApplication>

class Drone
{
 public:
        Drone(cv::Mat *frame);
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
	StatusController _statusController;
        VideoController _videoController;

	std::thread _videoThread;
	std::thread _statusThread;

	StatusParams _statusParams;
};

#pragma once

#include "TelloDriver.h"
#include <thread>
#include <mutex>

class CommandController
{
 public:
	CommandController(TelloDriver *telloDriver);
	bool execuiteCommand(const std::string &command);

 private:
	TelloDriver *_telloDriver;

	const int _maxMissedPkg = 10;
	const int _waitTime = 5000000;
};
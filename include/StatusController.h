#pragma once

#include <iostream>

#include "TelloDriver.h"

class StatusController
{
 public:
	explicit StatusController(TelloDriver *tello_driver);
	~StatusController();

//	void showTelloInfo();

	StatusParams getStatus();

	bool isAlive() const;

 private:
	bool _alive = false;
	TelloDriver *_telloDriver;
};
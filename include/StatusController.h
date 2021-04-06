#pragma once

#include <iostream>

#include "TelloDriver.h"

class StatusController
{
 public:
	explicit StatusController(TelloDriver *tello_driver);

//	void showTelloInfo();

	StatusParams getStatus();

	bool isAlive() const;

	void setAlive(bool alive);

 private:
	bool _alive = false;
	TelloDriver tello_driver;
};
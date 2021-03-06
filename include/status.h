#pragma once

#include <iostream>
#include "tello_driver.h"

class Tello_status
{
 public:
	explicit Tello_status(Tello* tello_driver);

	void showTelloInfo();
	std::string getStatus();

 private:
	Tello * const tello_driver;

};
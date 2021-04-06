#pragma once

#include "TelloDriver.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"


class VideoController
{
 public:
	explicit VideoController(TelloDriver *tello_driver);

	void getVideo();

	bool isAlive() const;
	void setAlive(bool alive);

 private:
 	bool _alive = false;
	TelloDriver tello_driver;
	const char* const TELLO_STREAM_URL{"udp://0.0.0.0:11111"};
};
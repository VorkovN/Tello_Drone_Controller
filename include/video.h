#pragma once

#include <thread>
#include "driver.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"


class Tello_video
{
 public:
	explicit Tello_video(Tello *tello_driver);
	void getVideo();
	void startVideo();
	void stopVideo();

 private:


 private:
	const char* const TELLO_STREAM_URL{"udp://0.0.0.0:11111"};
 	bool flag;
 	std::thread thread;
	Tello * const tello_driver;
};
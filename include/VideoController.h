#pragma once

#include "TelloDriver.h"
#include "CommandController.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

class VideoController
{
 public:
        explicit VideoController(CommandController *commandController, cv::Mat *frame);

	void getVideo();

	bool isAlive() const;
	void setAlive(bool alive);

 private:
 	bool _alive = false;
	CommandController *_commandController;
	const char* const TELLO_STREAM_URL{"udp://0.0.0.0:11111"};
    cv::Mat *_frame;
};

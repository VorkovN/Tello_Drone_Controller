#pragma once

#include "TelloDriver.h"
#include "CommandController.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"


class VideoController
{
 public:
	explicit VideoController(CommandController *commandController);
	~VideoController();

	void getVideo();

    bool isAlive() const;
    void setAlive(bool alive);

public:
    static cv::Mat frame;
    static bool _alive;

 private:

	CommandController *_commandController;
	const char* const TELLO_STREAM_URL{"udp://0.0.0.0:11111"};
};
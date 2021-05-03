#pragma once

#include "TelloDriver.h"
#include "CommandController.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"


class VideoController
{
 public:
	VideoController(CommandController *commandController);
	~VideoController();

    cv::Mat getVideoFrame();

 private:
    cv::Mat _frame;
    cv::VideoCapture _capture;
	CommandController *_commandController;
	const char* const TELLO_STREAM_URL;
};
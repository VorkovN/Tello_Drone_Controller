#include "VideoController.h"

VideoController::VideoController(CommandController *commandController): _commandController(commandController)
{
}

void VideoController::getVideo()
{
	std::cout << "Video Ok: " << _commandController->execuiteCommand("streamon");

	cv::VideoCapture capture(TELLO_STREAM_URL, cv::CAP_FFMPEG);
	cv::Mat frame;
	while (cv::waitKey(1) != 27 && _alive)
	{
		capture >> frame;
		imshow("TelloDriver video", frame);
	}

}

bool VideoController::isAlive() const
{
	return _alive;
}

void VideoController::setAlive(bool alive)
{
	_alive = alive;
}

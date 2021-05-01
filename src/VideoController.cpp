#include "VideoController.h"

cv::Mat VideoController::frame = {};
bool VideoController::_alive = false;

VideoController::VideoController(CommandController *commandController): _commandController(commandController)
{

}

void VideoController::getVideo()
{
	std::cout << "Video Ok: " << _commandController->execuiteCommand("streamon");

	cv::VideoCapture capture(TELLO_STREAM_URL, cv::CAP_FFMPEG);

	while (_alive)
		capture >> frame;
}

bool VideoController::isAlive() const
{
    return _alive;
}

void VideoController::setAlive(bool alive)
{
    _alive = alive;
}

VideoController::~VideoController()
{
    _alive = false;
}


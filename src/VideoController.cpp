#include "VideoController.h"

VideoController::VideoController(TelloDriver *tello_driver): tello_driver(*tello_driver)
{
}

void VideoController::getVideo()
{

	tello_driver.sendCommand("streamon");
	while (tello_driver.receiveResponse().empty());

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

#include "VideoController.h"

VideoController::VideoController(CommandController *commandController, cv::Mat* frame):
    _commandController(commandController), _frame(frame)
{
}

void VideoController::getVideo()
{
	std::cout << "Video Ok: " << _commandController->execuiteCommand("streamon");

	cv::VideoCapture capture(TELLO_STREAM_URL, cv::CAP_FFMPEG);

    while (_alive)
    {
        capture >> *_frame;
//        std::cout << "FRAME0: " << _frame->size << std::endl;
//        usleep(50000);
//		imshow("TelloDriver video", frame);
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

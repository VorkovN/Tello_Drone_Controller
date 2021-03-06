#include "VideoController.h"

VideoController::VideoController(CommandController *commandController): _commandController(commandController), TELLO_STREAM_URL("udp://0.0.0.0:11111")
{
    _commandController->execuiteCommand("streamon");
    _capture = cv::VideoCapture(TELLO_STREAM_URL, cv::CAP_FFMPEG);
    std::cout << "VideoController has been created" << std::endl;
}

cv::Mat VideoController::getVideoFrame()
{
    _capture >> _frame;
    return _frame;
}

VideoController::~VideoController()
{
    std::cout << "VideoController destroyed" << std::endl;
}


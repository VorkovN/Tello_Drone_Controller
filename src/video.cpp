#include "video.h"

Tello_video::Tello_video(Tello *tello_driver): tello_driver(tello_driver), flag(true)
{
	thread = std::thread(&Tello_video::getVideo, this);

}

void Tello_video::getVideo()
{

	tello_driver->sendCommand("streamon");
	while (tello_driver->receiveResponse().empty());

	cv::VideoCapture capture(TELLO_STREAM_URL, cv::CAP_FFMPEG);
	cv::Mat frame;
	while (cv::waitKey(1) != 27 && flag)//todo delete
	{
		capture >> frame;
		imshow("Tello video", frame);
	}

}

void Tello_video::startVideo()
{
	flag = true;
	thread.detach();
}

void Tello_video::stopVideo()
{
	flag = false;
}

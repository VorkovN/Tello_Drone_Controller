// https://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D0%BA%D0%B5%D1%82%D1%8B_%D0%91%D0%B5%D1%80%D0%BA%D0%BB%D0%B8
// https://dl-cdn.ryzerobotics.com/downloads/tello/0228/Tello+SDK+Readme.pdf

#include <iostream>
#include "driver.h"
#include "status.h"
#include "video.h"

int main()
{
	Tello *tello = new Tello();

	sleep(1);

	Tello_status *telloStatus = new Tello_status(tello);
	Tello_video *telloVideo = new Tello_video(tello);
	sleep(1);

	telloVideo->startVideo();
	std::cout << telloStatus->getStatus();
	sleep(5);
//	sleep(5);
//	telloVideo->stopVideo();
//	sleep(5);

//	//тестирование взлета и посадки
//	tello->sendCommand("takeoff");
//	std::string response1;
//	while ((response1 = tello->receiveResponse()).empty());
//	std::cout << response1 << std::endl;
//	sleep(1);
//	tello->sendCommand("land");
//	std::string response2;
//	while ((response2 = tello->receiveResponse()).empty());
//	std::cout << response2 << std::endl;

	return 0;
}

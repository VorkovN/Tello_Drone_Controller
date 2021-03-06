#include "status.h"

Tello_status::Tello_status(Tello * tello_driver) : tello_driver(tello_driver)
{

}

void Tello_status::showTelloInfo()
{
	std::cout << "Getting Tello info..." << std::endl;
	std::string response;

	tello_driver->sendCommand("speed?");
	while ((response = tello_driver->receiveResponse()).empty());
	std::cout << "Speed: " << response << std::endl;

	tello_driver->sendCommand("battery?");
	while ((response = tello_driver->receiveResponse()).empty());
	std::cout << "Battery: " << response << std::endl;
}

std::string Tello_status::getStatus()
{
	std::string status = tello_driver->receiveStatus();

	return status;
}




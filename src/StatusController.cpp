#include "StatusController.h"

StatusController::StatusController(TelloDriver *tello_driver) : tello_driver(*tello_driver)
{
}

//void StatusController::showTelloInfo()
//{
//	std::cout << "Getting TelloDriver info..." << std::endl;
//	std::string response;
//
//	tello_driver.sendCommand("speed?");
//	while ((response = tello_driver.receiveResponse()).empty());
//	std::cout << "Speed: " << response << std::endl;
//
//	tello_driver.sendCommand("battery?");
//	while ((response = tello_driver.receiveResponse()).empty());
//	std::cout << "Battery: " << response << std::endl;
//}

StatusParams StatusController::getStatus()
{
	StatusParams statusParams;
	std::string status = tello_driver.receiveStatus();
	
	size_t prev = status.find(':');
	size_t next = status.find(';');
	statusParams._pitch = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._roll = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._yaw = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._vgx = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._vgy = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._vgz = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._templ = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._temph = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._tof = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._h = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._bat = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._baro = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._time = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._agx = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._agy = std::stod(status.substr(prev+1, next-prev));
	prev = status.find(':',++prev);
	next = status.find(';',++next);
	statusParams._agz = std::stod(status.substr(prev+1, next-prev));

	return statusParams;
}

bool StatusController::isAlive() const
{
	return _alive;
}

void StatusController::setAlive(bool alive)
{
	_alive = alive;
}




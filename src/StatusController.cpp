#include "StatusController.h"

StatusController::StatusController(TelloDriver *tello_driver) : _telloDriver(tello_driver)
{
    _alive = true;
    std::cout << "StatusController has been created" << std::endl;
}

//void StatusController::showTelloInfo()
//{
//	std::cout << "Getting TelloDriver info..." << std::endl;
//	std::string response;
//
//	_telloDriver.sendCommand("speed?");
//	while ((response = _telloDriver.receiveResponse()).empty());
//	std::cout << "Speed: " << response << std::endl;
//
//	_telloDriver.sendCommand("battery?");
//	while ((response = _telloDriver.receiveResponse()).empty());
//	std::cout << "Battery: " << response << std::endl;
//}

StatusParams StatusController::getStatus()
{
	StatusParams statusParams;
	std::string status = _telloDriver->receiveStatus().second;
	
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

StatusController::~StatusController()
{
    _alive = false;
}




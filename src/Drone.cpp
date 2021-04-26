#include "Drone.h"

Drone::Drone():_videoController(&_commandController), _statusController(&_telloDriver), _commandController(&_telloDriver)
{
	_commandController.execuiteCommand("command");
	sleep(1);//дрону нужно время на инициализацию
	_statusThread = std::thread(&Drone::saveStatus, this);
	_videoThread = std::thread(&VideoController::getVideo, &_videoController);

	receiveStatus();
	startVideo();
}

bool Drone::executeCommand(const std::string& command)
{
	return _commandController.execuiteCommand(command);
}

void Drone::saveStatus()
{
	_statusController.setAlive(true);
	while (_statusController.isAlive())
	{
		_statusParams = _statusController.getStatus();
		sleep(1);
		printStatus();
	}

}

void Drone::receiveStatus()
{
	_videoController.setAlive(true);
	_statusThread.detach();
}

void Drone::printStatus() const
{
	 std::cout << " _pitch: " << _statusParams._pitch << std::endl;
	 std::cout << " _roll:  " << _statusParams._roll  << std::endl;
	 std::cout << " _yaw:   " << _statusParams._yaw   << std::endl;
	 std::cout << " _vgx:   " << _statusParams._vgx   << std::endl;
	 std::cout << " _vgy:   " << _statusParams._vgy   << std::endl;
	 std::cout << " _vgz:   " << _statusParams._vgz   << std::endl;
	 std::cout << " _templ: " << _statusParams._templ << std::endl;
	 std::cout << " _temph: " << _statusParams._temph << std::endl;
	 std::cout << " _tof:   " << _statusParams._tof   << std::endl;
	 std::cout << " _h:     " << _statusParams._h     << std::endl;
	 std::cout << " _bat:   " << _statusParams._bat   << std::endl;
	 std::cout << " _baro:  " << _statusParams._baro  << std::endl;
	 std::cout << " _time:  " << _statusParams._time  << std::endl;
	 std::cout << " _agx:   " << _statusParams._agx   << std::endl;
	 std::cout << " _agy:   " << _statusParams._agy   << std::endl;
	 std::cout << " _agz:   " << _statusParams._agz   << std::endl;
}

void Drone::startVideo()
{
	_videoController.setAlive(true);
	_videoThread.detach();
}

void Drone::stopVideo()
{
	_videoController.setAlive(false);
}

Drone::~Drone()
{
	_statusController.setAlive(false);
	_videoController.setAlive(false);
	sleep(2);
}


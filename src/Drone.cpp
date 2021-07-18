#include "Drone.h"

Drone::Drone():_commandController(&_telloDriver), _statusController(&_telloDriver), _videoController(&_commandController)
{
    std::cout << "Drone has been created" << std::endl;
}

bool Drone::executeCommand(std::string command)
{
	return _commandController.execuiteCommand(command);
}

void Drone::checkStatus()
{
    _statusParams = _statusController.getStatus();
    //todo возможна логика по обработке
}

cv::Mat Drone::returnVideoFrame()
{
    //todo возможна логика по обработке
    return _videoController.getVideoFrame();
}
QString Drone::returnStatus()
{
    checkStatus();
    QString qString{(
    " _pitch: " + std::to_string(_statusParams._pitch) + "\n" +
    " _roll:  " + std::to_string(_statusParams._roll)  + "\n" +
    " _yaw:   " + std::to_string(_statusParams._yaw)   + "\n" +
    " _vgx:   " + std::to_string(_statusParams._vgx)   + "\n" +
    " _vgy:   " + std::to_string(_statusParams._vgy)   + "\n" +
    " _vgz:   " + std::to_string(_statusParams._vgz)   + "\n" +
    " _templ: " + std::to_string(_statusParams._templ) + "\n" +
    " _temph: " + std::to_string(_statusParams._temph) + "\n" +
    " _tof:   " + std::to_string(_statusParams._tof)   + "\n" +
    " _h:     " + std::to_string(_statusParams._h)     + "\n" +
    " _bat:   " + std::to_string(_statusParams._bat)   + "\n" +
    " _baro:  " + std::to_string(_statusParams._baro)  + "\n" +
    " _time:  " + std::to_string(_statusParams._time)  + "\n" +
    " _agx:   " + std::to_string(_statusParams._agx)   + "\n" +
    " _agy:   " + std::to_string(_statusParams._agy)   + "\n" +
    " _agz:   " + std::to_string(_statusParams._agz)   + "\n").c_str()};
    return qString;
}

Drone::~Drone()
{
	sleep(2);
}


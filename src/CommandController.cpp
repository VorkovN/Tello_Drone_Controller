#include "CommandController.h"

CommandController::CommandController(TelloDriver *telloDriver): _telloDriver(telloDriver)
{
    execuiteCommand("command");
    sleep(1);//время на инициализацию дрона
    execuiteCommand("speed 100");
    sleep(1);
    std::cout << "CommandController has been created" << std::endl;
}

bool CommandController::execuiteCommand(const std::string &command)
{

	for (int i = 0; i < _maxMissedPkg; ++i)
	{
		bool waiting = true;//в ожидании ответа

		std::thread([&](){usleep(_waitTime); waiting = false;}).detach();//запускаем таймер

		std::cout << "command: " << command << "sended status: " << _telloDriver->sendCommand(command) << std::endl;//отправляем команду

		while (!_telloDriver->receiveResponse().first)//пока не получен ответ проверяем
			if (!waiting)//если время вышло
				break;//повторная отправка

		if (!waiting)
			continue;

		std::cout << "command: " << command << " DONE" << std::endl;

		return true;

	}

	std::cout << "command: " << command << " ERROR" << std::endl;
	return false;
}

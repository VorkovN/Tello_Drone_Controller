#include "CommandController.h"

CommandController::CommandController(TelloDriver *telloDriver): _telloDriver(telloDriver)
{
    execuiteCommand("command");
    sleep(1);//время на инициализацию дрона
    std::cout << "CommandController has been created" << std::endl;
}

bool CommandController::execuiteCommand(const std::string &command)
{
	senderMutex.lock();
	for (int i = 0; i < _maxMissedPkg; ++i)
	{
		bool waiting = true;//в ожидании ответа

		std::thread([&](){usleep(_waitTime); waiting = false;}).detach();//запускаем таймер

		_telloDriver->sendCommand(command);//отправляем команду

		while (!_telloDriver->receiveResponse().first)//пока не получен ответ проверяем
			if (!waiting)//если время вышло
				break;//повторная отправка

		if (!waiting)
			continue;

		std::cout << "command: " << command << " DONE" << std::endl;
		senderMutex.unlock();
		return true;

	}

	std::cout << "command: " << command << " ERROR" << std::endl;
	senderMutex.unlock();
	return false;
}

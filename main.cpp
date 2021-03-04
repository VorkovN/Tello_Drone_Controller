#include <iostream>
#include "tello_driver.h"

int main()
{
	Tello tello{};
	if (!tello.bindSockets())
	{
		std::cout << "Binding error";
		return 0;
	}
	tello.findTello();//отправка инициализирующей команды
	sleep(1);
	
	tello.showTelloInfo();//получить некоторые данные

	sleep(1);

	//тестирование взлета и посадки
	tello.sendCommand("takeoff");
	std::string response1;
	while ((response1 = tello.receiveResponse()).empty());
	std::cout << response1 << std::endl;
	sleep(1);
	tello.sendCommand("land");
	std::string response2;
	while ((response2 = tello.receiveResponse()).empty());
	std::cout << response2 << std::endl;
	//

//тестирование отображения статуса
//	std::cout << tello.GetState();
	return 0;
}

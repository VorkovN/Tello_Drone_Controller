#include "Drone.h"

int main()
{
	Drone drone;
	sleep(1);
	drone.executeCommand("takeoff");
	sleep(8);
	drone.executeCommand("land");
	sleep(2);
	return 0;
}

// программное обеспечение всроенных систем, модели вычисления
// ли проблема с потоками
// основание программированияы
// мифический человек и месяц брукс
// Гради Бутч объектно-ориентированный анализ и проектирование


#include <QApplication>
#include "Drone.h"

#include "DroneWindow.h"


int main(int argc, char *argv[])
{
//    sleep(1);
//    drone.executeCommand("takeoff");
//    sleep(8);
//    drone.executeCommand("land");
//    sleep(2);

    QApplication app(argc, argv);
    DroneWindow window;

    window.setWindowTitle("Tello");
    window.showNormal();
    return app.exec();
}

// программное обеспечение всроенных систем, модели вычисления
// ли проблема с потоками
// основание программированияы
// мифический человек и месяц брукс
// Гради Бутч объектно-ориентированный анализ и проектирование


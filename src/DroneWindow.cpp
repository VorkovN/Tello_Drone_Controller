#include "DroneWindow.h"


DroneWindow::DroneWindow(QWidget *parent): QWidget(parent), _rect(QApplication::desktop()->screenGeometry())
{
//создание кнопки старт
//    _startBtn = new QPushButton("Start\nvideo", this); // создаем новую кнопку
//    _startBtn->setGeometry(0.8 * _rect.width(), 0.75 * _rect.height(), 0.075 * _rect.width(), 0.1 * _rect.height()); // изменяем размеры кнопки в пикселях и помещаем на форму окна
//    connect(_startBtn, &QPushButton::clicked, this, &DroneWindow::onStartVideoButtonClick);
//
//    //создание кнопки стоп
//    _stopBtn = new QPushButton("Stop\nvideo", this); // создаем новую кнопку
//    _stopBtn->setGeometry(0.875 * _rect.width(), 0.75 * _rect.height(), 0.075 * _rect.width(), 0.1 * _rect.height()); // изменяем размеры кнопки в пикселях и помещаем на форму окна
//    connect(_stopBtn, &QPushButton::clicked, this, &DroneWindow::onStopVideoButtonClick);

    //создание кнопки выход
    _quitBtn = new QPushButton("Finish the flight", this);
    _quitBtn->setGeometry(0.8 * _rect.width(), 0.85 * _rect.height(), 0.15 * _rect.width(), 0.075 * _rect.height());
    connect(_quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    //создание пространства под видео
    _frameLabel = new QLabel(this);
    _frameLabel->setGeometry(0, 0, 0.75 * _rect.width(), _rect.height());

    _statusLabel = new QLabel(this);
    _statusLabel->setGeometry(0.775 * _rect.width(), 0.02 * _rect.height(), 0.2 * _rect.width(), 0.35 * _rect.height());

    _helpLabel = new QLabel(this);
    _helpLabel->setGeometry(0.775 * _rect.width(), 0.38 * _rect.height(), 0.2 * _rect.width(), 0.35 * _rect.height());
    _helpLabel->setText("Help\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp");

    _statusTimerId = startTimer(constants::STATUS_DELAY);
    _videoTimerId = startTimer(constants::VIDEO_FRAME_DELAY);

    std::cout << "Window has been created" << std::endl;
}

void DroneWindow::timerEvent(QTimerEvent *e) {

    if (e->timerId() == _videoTimerId)
        updateVideoFrame();

    if (e->timerId() == _statusTimerId)
        updateStatus();
}

//void DroneWindow::onStartVideoButtonClick()
//{
//    _drone.startVideo();
//    sleep(1);
//    std::cout << "startBtn" << std::endl;
//}

//void DroneWindow::onStopVideoButtonClick()
//{
//    _drone.stopVideo();
//    killTimer(_videoTimerId);
//    std::cout << "stopBtn" << std::endl;
//}

DroneWindow::~DroneWindow()
{
    killTimer(_statusTimerId);
    killTimer(_statusTimerId);
    std::cout << "theEnd" << std::endl;
}
void DroneWindow::updateVideoFrame()
{
    cv::Mat frame = _drone.returnVideoFrame();
    std::cout << frame.size << std::endl;
    QImage img(frame.data, frame.cols, frame.rows, QImage::Format_BGR888);
    QPixmap pixmap = QPixmap::fromImage(img);
    _frameLabel->setPixmap(pixmap.scaled(0.75 * _rect.width(), _rect.height()));
    repaint();
}
void DroneWindow::updateStatus()
{
    _statusLabel->setText(_drone.returnStatus());
    repaint();
}


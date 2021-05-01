#include "DroneWindow.h"


DroneWindow::DroneWindow(QWidget *parent): QWidget(parent), _rect(QApplication::desktop()->screenGeometry())
{
//создание кнопки старт
    _startBtn = new QPushButton("Start", this); // создаем новую кнопку
    _startBtn->setGeometry(0.8 * _rect.width(), 0.8 * _rect.height(), 0.075 * _rect.width(), 0.1 * _rect.height()); // изменяем размеры кнопки в пикселях и помещаем на форму окна
    connect(_startBtn, &QPushButton::clicked, this, &DroneWindow::onStartButtonClick);

    //создание кнопки стоп
    _stopBtn = new QPushButton("Stop", this); // создаем новую кнопку
    _stopBtn->setGeometry(0.875 * _rect.width(), 0.8 * _rect.height(), 0.075 * _rect.width(), 0.1 * _rect.height()); // изменяем размеры кнопки в пикселях и помещаем на форму окна
    connect(_stopBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    //создание пространства под видео
    _frameLabel = new QLabel(this);
    _frameLabel->setGeometry(0, 0, 0.75 * _rect.width(), _rect.height());

    _timerId = startTimer(DELAY);
}

void DroneWindow::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

        QImage img(VideoController::frame.data, VideoController::frame.cols, VideoController::frame.rows, QImage::Format_BGR888);
        QPixmap pixmap = QPixmap::fromImage(img);
        _frameLabel->setPixmap(pixmap.scaled(0.75 * _rect.width(), _rect.height()));

    repaint();
}

void DroneWindow::onStartButtonClick()
{
    _drone.startVideo();
    std::cout << "startBtn" << std::endl;
}

DroneWindow::~DroneWindow()
{
    _drone.stopVideo();
    killTimer(_timerId);
    std::cout << "theEnd" << std::endl;
}


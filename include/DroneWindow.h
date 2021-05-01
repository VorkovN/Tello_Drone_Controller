#pragma once

//#include <pthread.h>

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRect>

#include "Drone.h"

class DroneWindow: public QWidget
{
public:
    explicit DroneWindow(QWidget *parent = nullptr);
    ~DroneWindow() override;

private slots:
    void timerEvent(QTimerEvent *) override;
    void onStartButtonClick();

private:
    QRect _rect;//параметры экрана
    QLabel *_frameLabel;
    QPushButton *_startBtn;
    QPushButton *_stopBtn;
    std::thread _videoThread;
    int _timerId;
    uint32_t  DELAY = 1;

    Drone _drone;

};